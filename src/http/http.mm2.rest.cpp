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

#include "http.mm2.rest.hpp"

namespace antara::mmbot::http::rest
{

    mm2::mm2(const config &cfg, mm2_client &mm2_client) noexcept : mmbot_config_(cfg), mm2_client_(mm2_client)
    {
        VLOG_SCOPE_F(loguru::Verbosity_INFO, pretty_function);
    }

    mm2::~mm2() noexcept
    {
        VLOG_SCOPE_F(loguru::Verbosity_INFO, pretty_function);
    }

    restinio::request_handling_status_t
    mm2::get_orderbook(const restinio::request_handle_t &req, const restinio::router::route_params_t &)
    {
        VLOG_SCOPE_F(loguru::Verbosity_INFO, pretty_function);
        DVLOG_F(loguru::Verbosity_INFO, "http call: %s", "/api/v1/legacy/mm2");
        const auto query_params = restinio::parse_query(req->header().query());
        if (query_params.size() != 2) {
            DVLOG_F(loguru::Verbosity_ERROR,
                    "Not enough parameters, require base_currency and quote_currency parameters");
            return req->create_response(restinio::status_bad_request()).done();
        }
        if (!query_params.has("base_currency") || !query_params.has("quote_currency")) {
            DVLOG_F(loguru::Verbosity_ERROR, "Wrong parameters, require base_asset and quote_asset parameters");
            return req->create_response(restinio::status_unprocessable_entity()).done();
        }
        antara::mmbot::mm2::orderbook_request orderbook_request{
                antara::pair::of(std::string(query_params["quote_currency"]), std::string(query_params["base_currency"]))};
        auto orderbook_answer = mm2_client_.rpc_orderbook(std::move(orderbook_request));
        auto answer_json = nlohmann::json::parse(orderbook_answer.result);
        auto final_status = restinio::http_status_line_t(
                static_cast<restinio::http_status_code_t>(orderbook_answer.rpc_result_code), "");
        return req->create_response(final_status).set_body(answer_json.dump()).done();
    }
}