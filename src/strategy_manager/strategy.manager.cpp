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

#include "strategy.manager.hpp"

namespace antara::mmbot
{
    void from_json (const nlohmann::json &j, antara::pair &p)
    {
        VLOG_SCOPE_F(loguru::Verbosity_INFO, pretty_function);
        p.base = antara::asset{st_symbol{j.at("base").get<std::string>()}};
        p.quote = antara::asset{st_symbol{j.at("quote").get<std::string>()}};
    }

    void to_json(nlohmann::json &j, const antara::pair &p)
    {
        VLOG_SCOPE_F(loguru::Verbosity_INFO, pretty_function);
        j["base"] = p.base.symbol.value();
        j["quote"] = p.quote.symbol.value();
    }

    void from_json (const nlohmann::json &j, market_making_strategy &mms)
    {
        VLOG_SCOPE_F(loguru::Verbosity_INFO, pretty_function);
        from_json(j.at("pair"), mms.pair);
        mms.spread = st_spread{j.at("spread").get<double>()};
        mms.quantity = st_quantity{j.at("quantity").get<double>()};
        if (j.find("both") != j.end()) {
            j.at("both").get_to(mms.both);
        }
    }

    void to_json (nlohmann::json &j, const market_making_strategy &mms)
    {
        nlohmann::json p;
        to_json(j["pair"], mms.pair);
        j["spread"] = mms.spread.value();
        j["quantity"] = mms.quantity.value();
        j["both"] = mms.both;
    }
}
