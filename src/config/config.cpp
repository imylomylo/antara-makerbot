/******************************************************************************
 * Copyright © 2013-2019 The Komodo Platform Developers.                      *
 *                                                                            *
 * See the AUTHORS, DEVELOPER-AGREEMENT and LICENSE files at                  *
 * the top-level directory of this distribution for the individual copyright  *
 * holder information and the developer policies on copyright and licensing.  *
 *                                                                            *
 * Unless otherwise agreed in a custom licensing agreement, no part of the    *
 * Komodo Platform software, including this file may be copied, modified,     *
 * propagated or distributed except according to the terms contained in the   *
 * LICENSE file                                                               *
 *                                                                            *
 * Removal or modification of this copyright notice is prohibited.            *
 *                                                                            *
 ******************************************************************************/

#include "config.hpp"

namespace antara::mmbot
{
    static config mmbot_cfg;

    void from_json(const nlohmann::json &j, cex_config &cfg)
    {
        cfg.cex_endpoint = st_endpoint{j.at("cex_endpoint").get<std::string>()};
        cfg.cex_public_key = st_key{j.at("cex_api_public_key").get<std::string>()};
        cfg.cex_private_key = st_key{j.at("cex_api_private_key").get<std::string>()};
    }

    void from_json(const nlohmann::json &j, price_config &cfg)
    {
        cfg.price_endpoint = st_endpoint{j.at("price_endpoint").get<std::string>()};
        if (j.count("price_api_key") > 0) {
            cfg.price_api_key = st_key{j.at("price_api_key").get<std::string>()};
        }
    }

    void from_json(const nlohmann::json &j, config &cfg)
    {
        j.at("cex_infos_registry").get_to(cfg.cex_registry);
        j.at("price_infos_registry").get_to(cfg.price_registry);
        j.at("http_port").get_to(cfg.http_port);
    }

    void to_json(nlohmann::json &j, const cex_config &cfg)
    {
        j["cex_endpoint"] = cfg.cex_endpoint.value();
        j["cex_api_public_key"] = cfg.cex_public_key.value();
        j["cex_api_private_key"] = cfg.cex_private_key.value();
    }

    void to_json(nlohmann::json &j, const price_config &cfg)
    {
        j["price_endpoint"] = cfg.price_endpoint.value();
        if (cfg.price_api_key.has_value()) {
            j["price_api_key"] = cfg.price_api_key.value().value();
        }
    }

    void to_json(nlohmann::json &j, const config &cfg)
    {
        j["cex_infos_registry"] = nlohmann::json::object();
        for (auto&&[key, value] : cfg.cex_registry) {
            j["cex_infos"][key] = value;
        }
        j["price_infos_registry"] = nlohmann::json::object();
        for (auto&&[key, value] : cfg.price_registry) {
            j["price_infos"][key] = value;
        }
        j["http_port"] = cfg.http_port;
    }

    void load_mmbot_config(std::filesystem::path &&config_path, std::string filename) noexcept
    {
        VLOG_SCOPE_F(loguru::Verbosity_INFO, pretty_function);
        mmbot_cfg = load_configuration<mmbot::config>(std::forward<std::filesystem::path>(config_path),
                                                      std::move(filename));
        fill_with_coins_cfg(config_path, mmbot_cfg);
        auto full_path = config_path / "MM2.json";
        std::ifstream ifs(full_path);
        DCHECK_F(ifs.is_open(), "Failed to open: [%s]", full_path.string().c_str());
        nlohmann::json coins_json_data;
        ifs >> coins_json_data;
        coins_json_data.at("rpc_password").get_to(mmbot_cfg.mm2_rpc_password);
        ifs.close();
        if (auto force_passphrase = std::getenv("FORCE_MM2_PASSPHRASE"); force_passphrase != nullptr) {
            VLOG_F(loguru::Verbosity_INFO, "passphrase detected through environment, setuping...");
            std::ofstream ofs(full_path, std::ios::trunc);
            DCHECK_F(ofs.is_open(), "Failed to open: [%s]", full_path.string().c_str());
            coins_json_data["passphrase"] = force_passphrase;
            ofs << coins_json_data;
            ofs.close();
        }
    }

    void fill_with_coins_cfg(const std::filesystem::path &config_path, config &cfg)
    {
        VLOG_SCOPE_F(loguru::Verbosity_INFO, pretty_function);
        auto full_path = config_path / "coins.json";
        std::ifstream ifs(full_path);
        DCHECK_F(ifs.is_open(), "Failed to open: [%s]", full_path.string().c_str());
        nlohmann::json coins_json_data;
        ifs >> coins_json_data;
        for (auto &&current_element: coins_json_data) {
            additional_coin_info additional_infos{8u, false, false, {}};
            auto current_coin = current_element["coin"].get<std::string>();
            if (current_element.find("etomic") != current_element.end() &&
                current_element.find("decimals") == current_element.end()) {
                additional_infos.nb_decimals = 18;
            } else if (current_element.find("etomic") != current_element.end() &&
                       current_element.find("decimals") != current_element.end()) {
                additional_infos.nb_decimals = current_element["decimals"].get<int>();
            }
            additional_infos.is_mm2_compatible = current_element.find("mm2") != current_element.end();
            auto current_path = std::filesystem::current_path() / "assets/electrums" / current_coin;
            if (additional_infos.is_mm2_compatible &&
                std::filesystem::exists(current_path)) {
                additional_infos.is_electrum_compatible = true;
            }
            if (additional_infos.is_electrum_compatible) {
                extract_from_electrum_file(config_path, current_coin, additional_infos);
            }
            cfg.registry_additional_coin_infos.emplace(current_coin,
                                                       additional_infos);
        }
        cfg.registry_additional_coin_infos.emplace("EUR", additional_coin_info{2u, false, false, {}});
        cfg.registry_additional_coin_infos.emplace("USD", additional_coin_info{2u, false, false, {}});
    }

    void extract_from_electrum_file(const std::filesystem::path &path, const std::string &coin,
                                    additional_coin_info &additional_info)
    {
        VLOG_SCOPE_F(loguru::Verbosity_INFO, pretty_function);
        auto full_path = path / "electrums" / coin;
        std::ifstream ifs(full_path);
        DCHECK_F(ifs.is_open(), "Failed to open: [%s]", full_path.string().c_str());
        nlohmann::json electrum_json_data;
        ifs >> electrum_json_data;
        for (auto &&current_element: electrum_json_data) {
            electrum_server srv;
            current_element.at("url").get_to(srv.url);
            if (current_element.find("protocol") != current_element.end()) {
                srv.protocol = current_element.at("protocol").get<std::string>();
            }
            if (current_element.find("disable_cert_verification") != current_element.end()) {
                srv.disable_cert_verification = current_element.at("disable_cert_verification").get<bool>();
            }
            additional_info.servers_electrum.emplace_back(std::move(srv));
        }
    }

    void to_json(nlohmann::json &j, const electrum_server &cfg)
    {
        j["url"] = cfg.url;
        if (cfg.protocol.has_value()) {
            j["protocol"] = cfg.protocol.value();
        }
        if (cfg.disable_cert_verification.has_value()) {
            j["disable_cert_verification"] = cfg.disable_cert_verification.value();
        }
    }

    const mmbot::config &get_mmbot_config() noexcept
    {
        return mmbot_cfg;
    }

    void set_mmbot_config(config &cfg) noexcept
    {
        mmbot_cfg = cfg;
    }

    bool config::operator==(const config &rhs) const
    {
        return cex_registry == rhs.cex_registry &&
               price_registry == rhs.price_registry &&
               http_port == rhs.http_port && mm2_rpc_password == rhs.mm2_rpc_password;
    }

    bool config::operator!=(const config &rhs) const
    {
        return !(rhs == *this);
    }

    bool price_config::operator==(const price_config &rhs) const
    {
#ifdef _MSC_VER
        if (price_api_key.has_value() && rhs.price_api_key.has_value()) {
             return price_endpoint.value() == rhs.price_endpoint.value()
                    && price_api_key.value().value() == rhs.price_api_key.value().value();
        } else {
            return price_endpoint.value() == rhs.price_endpoint.value();
        }
#else
        return price_endpoint.value() == rhs.price_endpoint.value()
               && price_api_key == rhs.price_api_key;
#endif
    }

    bool price_config::operator!=(const price_config &rhs) const
    {
        return !(rhs == *this);
    }

    bool cex_config::operator==(const cex_config &rhs) const
    {
        return cex_endpoint.value() == rhs.cex_endpoint.value() &&
               cex_public_key.value() == rhs.cex_public_key.value() &&
               cex_private_key.value() == rhs.cex_private_key.value();
    }

    bool cex_config::operator!=(const cex_config &rhs) const
    {
        return !(rhs == *this);
    }
}