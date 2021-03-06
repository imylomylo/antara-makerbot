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

#include <restinio/all.hpp>
#include "price/service.price.platform.hpp"

namespace antara::mmbot::http::rest
{
    class price
    {
    public:
        explicit price(price_service_platform &price_service) noexcept;

        ~price() noexcept;

        restinio::request_handling_status_t get_price(const restinio::request_handle_t& req, const restinio::router::route_params_t &);
        restinio::request_handling_status_t get_all_prices(const restinio::request_handle_t& req, const restinio::router::route_params_t &);
    private:
        price_service_platform &price_service_;
    };
}