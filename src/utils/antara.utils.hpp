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

#pragma once

#include <algorithm>
#include <cctype>
#include <locale>
#include <string>
#include "config/config.hpp"
#include "utils/mmbot_strong_types.hpp"

namespace antara
{
    [[nodiscard]] std::string get_price_as_string_decimal(const mmbot::config &cfg, const st_symbol &symbol, const st_symbol& original_symbol,
                                                          st_price price) noexcept;

    [[nodiscard]] st_price generate_st_price_from_api_price(const mmbot::config &cfg, const st_symbol &symbol,
                                                            std::string price_api_value) noexcept;

    std::string format_str_api_price(const mmbot::config &cfg, const st_symbol &symbol, std::string price_str);

    void extract_if_scientific(std::string &price_str);
    std::string unformat_str_to_representation_price(const mmbot::config &cfg, const st_symbol &symbol, const st_symbol& original_symbol,
                                                     std::string price_str);

    static inline void ltrim(std::string &s, const std::string &delimiters = " \f\n\r\t\v")
    {
        s.erase(0, s.find_first_not_of(delimiters));
    }

    struct my_json_sax : nlohmann::json_sax<nlohmann::json>
    {
        bool null() override;

        bool boolean(bool val) override;

        bool number_integer(number_integer_t val) override;

        bool number_unsigned(number_unsigned_t val) override;

        bool number_float(number_float_t val, const string_t &s) override;

        bool string(string_t &val) override;

        bool start_object(std::size_t elements) override;

        bool key(string_t &val) override;

        bool end_object() override;

        bool start_array(std::size_t elements) override;

        bool end_array() override;

        bool parse_error(std::size_t position, const std::string &last_token,
                         const nlohmann::detail::exception &ex) override;

        std::string float_as_string;
    };
}