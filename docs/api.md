# Rest Api Doc

## get all price from cache

Retrieve all the median price pairs of all komodo ecosystem coins

**URL**: `/api/v1/getallprice`

**Method**: `GET`

**Auth required**: No

**Permissions required**: None

**Prerequisites**: Program should be launched since atleast one minute (cache filling)

### Success Response

**Code**: `200 OK`

**Content examples**

```json
[
  {
    "RFOX": [
      {
        "RFOX/VRSC": "0.27409349"
      },
      {
        "RFOX/KMD": "0.03270390"
      },
      {
        "RFOX/DOGE": "9.38900572"
      },
      {
        "RFOX/BAT": "0.13624038"
      },
      {
        "RFOX/RVN": "0.73872477"
      },
      {
        "RFOX/ZILLA": "0.22130490"
      },
      {
        "RFOX/QTUM": "0.00992935"
      },
      {
        "RFOX/BTC": "0.00000243"
      },
      {
        "RFOX/LTC": "0.00033437"
      },
      {
        "RFOX/DASH": "0.00027411"
      },
      {
        "RFOX/DGB": "2.76478635"
      },
      {
        "RFOX/USDC": "0.02472535"
      },
      {
        "RFOX/ETH": "0.00013283"
      },
      {
        "RFOX/BCH": "0.00008210"
      }
    ]
  },
  {
    "VRSC": [
      {
        "VRSC/RFOX": "3.64839017"
      },
      {
        "VRSC/KMD": "0.11931659"
      },
      {
        "VRSC/DOGE": "34.25475619"
      },
      {
        "VRSC/BAT": "0.49705808"
      },
      {
        "VRSC/RVN": "2.69515619"
      },
      {
        "VRSC/ZILLA": "0.80740661"
      },
      {
        "VRSC/QTUM": "0.03622615"
      },
      {
        "VRSC/BTC": "0.00000888"
      },
      {
        "VRSC/LTC": "0.00121990"
      },
      {
        "VRSC/DASH": "0.00100008"
      },
      {
        "VRSC/DGB": "10.08701934"
      },
      {
        "VRSC/USDC": "0.09020775"
      },
      {
        "VRSC/ETH": "0.00048465"
      },
      {
        "VRSC/BCH": "0.00029954"
      }
    ]
  },
  {
    "KMD": [
      {
        "KMD/RFOX": "30.57739281"
      },
      {
        "KMD/VRSC": "8.38106435"
      },
      {
        "KMD/DOGE": "287.09131590"
      },
      {
        "KMD/BAT": "4.16587578"
      },
      {
        "KMD/RVN": "22.58827747"
      },
      {
        "KMD/ZILLA": "6.76692679"
      },
      {
        "KMD/QTUM": "0.30361373"
      },
      {
        "KMD/BTC": "0.00007441"
      },
      {
        "KMD/LTC": "0.01022409"
      },
      {
        "KMD/DASH": "0.00838172"
      },
      {
        "KMD/DGB": "84.53995820"
      },
      {
        "KMD/USDC": "0.75603698"
      },
      {
        "KMD/ETH": "0.00406189"
      },
      {
        "KMD/BCH": "0.00251046"
      }
    ]
  }
]
```

### Error response

200 + `null` in the body

## get price with an base currency and quote currency

Retrieves the median of the price of a base / quote currency pair

**URL**: `/api/v1/getprice?base_currency=:currency&quote_currency=:quote_currency`

**Method**: `GET`

**Auth required**: No

**Permissions required**: None

### Success Response

**Code**: `200 OK`

**Content examples**

```json
{
"price":"0.00007494"
}
```

### Error Response

**Code**: `400 Bad request` (Ill-formed request)

**Code**: `422 Unprocessable Entity` (Wrong Argument)

**Code**: `500 Internal Server Error` (Unexistent Base or Quote, throw pair not available)

## mm2 get orderbook with an base currency and quote currency

Retrieves the order book for the given asset pair

**URL**: `/api/v1/legacy/mm2/getorderbook?base_currency=:currency&quote_currency=:quote_currency`

**Method**: `GET`

**Auth required**: No

**Permissions required**: None

**Prerequisites**: `:currency and :quote_currency` should be enabled through `electrum` or `enable` rpc call.

### Success Response

**Code**: `200 OK`

**Content examples**

```json
{
  "askdepth": 0,
  "asks": [
    {
      "address": "RTpwruinq4GLbkGZg8NrJw5YPWUvMWnHYR",
      "age": 10,
      "avevolume": 0,
      "coin": "RICK",
      "depth": 0,
      "maxvolume": 969.8307168,
      "numutxos": 0,
      "price": 2,
      "pubkey": "9727ffa665389a4fed0a2b75687d1a7ad23a430f0aa06dfbf9edb9b972da7808",
      "zcredits": 0
    },
    {
      "address": "RT9MpMyucqXiX8bZLimXBnrrn2ofmdGNKd",
      "age": 3,
      "avevolume": 0,
      "coin": "RICK",
      "depth": 0,
      "maxvolume": 989.7500182,
      "numutxos": 0,
      "price": 2,
      "pubkey": "1bb83b58ec130e28e0a6d5d2acf2eb01b0d3f1670e021d47d31db8a858219da8",
      "zcredits": 0
    }
  ],
  "base": "RICK",
  "biddepth": 0,
  "bids": [
    {
      "address": "RTpwruinq4GLbkGZg8NrJw5YPWUvMWnHYR",
      "age": 10,
      "avevolume": 0,
      "coin": "MORTY",
      "depth": 0,
      "maxvolume": 963.1034758799999,
      "numutxos": 0,
      "price": 0.5,
      "pubkey": "9727ffa665389a4fed0a2b75687d1a7ad23a430f0aa06dfbf9edb9b972da7808",
      "zcredits": 0
    },
    {
      "address": "RT9MpMyucqXiX8bZLimXBnrrn2ofmdGNKd",
      "age": 4,
      "avevolume": 0,
      "coin": "MORTY",
      "depth": 0,
      "maxvolume": 973.91801759,
      "numutxos": 0,
      "price": 0.5,
      "pubkey": "1bb83b58ec130e28e0a6d5d2acf2eb01b0d3f1670e021d47d31db8a858219da8",
      "zcredits": 0
    }
  ],
  "netid": 0,
  "numasks": 2,
  "numbids": 2,
  "rel": "MORTY",
  "timestamp": 1565975342
}
```

### Error Response

**Code**: `400 Bad request` (Ill-formed request)

**Code**: `422 Unprocessable Entity` (Wrong Argument)

**Code**: `500 Internal Server Error` (Unexistent Base or Quote, Or `mm2` return 500 error code + message)

## mm2 get balance from a specific currency

Retrieve the balance of the given currency

**URL**: `/api/v1/legacy/mm2/my_balance?currency=:coin`

**Method**: `GET`

**Auth required**: No

**Permissions required**: None

**Prerequisites**: `:coin` should be enabled through `electrum` or `enable` rpc call.

### Success Response

**Code**: `200 OK`

**Content examples**

```json
{
  "address":"RRGKTckWwrZWq73vNekoLxqCJLHS4UKTyk",
  "balance":"0",
  "coin":"RICK"
}
```

### Error Response

**Code**: `400 Bad request` (Ill-formed request)

**Code**: `422 Unprocessable Entity` (Wrong Argument)

**Code**: `500 Internal Server Error` (Unexistent currency, Or `mm2` return 500 error code + message)

## mm2 get version

Retrieve the version of mm2

**URL**: `/api/v1/legacy/mm2/version`

**Method**: `GET`

**Auth required**: No

**Permissions required**: None


### Success Response

**Code**: `200 OK`

**Content examples**

```json
{
  "result":"2.0.1009_mm2_b08da3aa9_Darwin"
}
```

## mm2 my_orders

Retrieve the version of mm2

**URL**: `/api/v1/legacy/mm2/my_orders`

**Method**: `GET`

**Auth required**: No

**Permissions required**: None


### Success Response

**Code**: `200 OK`

**Content examples**

```json
{"result":{"maker_orders":{},"taker_orders":{}}}
```

## mm2 get enabled coins

Retrieve the enabled coins of mm2

**URL**: `/api/v1/legacy/mm2/get_enabled_coins`

**Method**: `GET`

**Auth required**: No

**Permissions required**: None


### Success Response

**Code**: `200 OK`

**Content examples**

```json
{
  "result": [
    {
      "address": "RDbAXLCmQ2EN7daEZZp7CC9xzkcN8DfAZd",
      "ticker": "RICK"
    },
    {
      "address": "RDbAXLCmQ2EN7daEZZp7CC9xzkcN8DfAZd",
      "ticker": "MORTY"
    }
  ]
}
```

## mm2 enable all electrums coins

Retrieve the enabled coins of mm2

**URL**: `/api/v1/mm2/enable_all_electrums_coins`

**Method**: `GET`

**Auth required**: No

**Permissions required**: None


### Success Response

**Code**: `200 OK`

**Content examples**

```json
{
  "result": [
    {
      "address": "VeJoMXUwD1L17Q7BqBUcXa9cvJSjvNNeyd",
      "ticker": "VTC"
    },
    {
      "address": "RDbAXLCmQ2EN7daEZZp7CC9xzkcN8DfAZd",
      "ticker": "MORTY"
    },
    {
      "address": "RDbAXLCmQ2EN7daEZZp7CC9xzkcN8DfAZd",
      "ticker": "ZEXO"
    },
    {
      "address": "RDbAXLCmQ2EN7daEZZp7CC9xzkcN8DfAZd",
      "ticker": "ILN"
    },
    {
      "address": "15JySpKUoCRo3dD36Ppz6fpmEV9mSDFjSf",
      "ticker": "BTC"
    },
    {
      "address": "QQuxZ7cByfJcUmJ4Wj9UDwcPjk6Uhec2Kv",
      "ticker": "QTUM"
    },
    {
      "address": "a52SBim71zRe7Ae96o97rx9GqrH7j5hsoZ",
      "ticker": "XZC"
    },
    {
      "address": "RDbAXLCmQ2EN7daEZZp7CC9xzkcN8DfAZd",
      "ticker": "RFOX"
    },
    {
      "address": "RDbAXLCmQ2EN7daEZZp7CC9xzkcN8DfAZd",
      "ticker": "OOT"
    },
    {
      "address": "RDbAXLCmQ2EN7daEZZp7CC9xzkcN8DfAZd",
      "ticker": "CHIPS"
    },
    {
      "address": "RDbAXLCmQ2EN7daEZZp7CC9xzkcN8DfAZd",
      "ticker": "KMD"
    },
    {
      "address": "EMTswQ9zE9ii2votuEpW6ooj18etw6VUnF",
      "ticker": "ECA"
    },
    {
      "address": "MCD8gFDtJDbbwJBNKNUvLwS6hi2vwswEED",
      "ticker": "MONA"
    },
    {
      "address": "GN9trweRn43686WL2LV6XSAf9ewcRCFbZY",
      "ticker": "GAME"
    },
    {
      "address": "t1NBaT9jcmXDPeGFw2pe7EUvgV9LrGCnyvi",
      "ticker": "ZEC"
    },
    {
      "address": "RDbAXLCmQ2EN7daEZZp7CC9xzkcN8DfAZd",
      "ticker": "KMDICE"
    },
    {
      "address": "RDbAXLCmQ2EN7daEZZp7CC9xzkcN8DfAZd",
      "ticker": "HUSH"
    },
    {
      "address": "RDbAXLCmQ2EN7daEZZp7CC9xzkcN8DfAZd",
      "ticker": "RICK"
    },
    {
      "address": "RDbAXLCmQ2EN7daEZZp7CC9xzkcN8DfAZd",
      "ticker": "RVN"
    },
    {
      "address": "RDbAXLCmQ2EN7daEZZp7CC9xzkcN8DfAZd",
      "ticker": "CCL"
    },
    {
      "address": "RDbAXLCmQ2EN7daEZZp7CC9xzkcN8DfAZd",
      "ticker": "CHAIN"
    },
    {
      "address": "D9T4z5G86cL5adPdpypYeRzN7ct4kGn9hQ",
      "ticker": "DOGE"
    },
    {
      "address": "EMTswQ9zE9ii2votuEpW6ooj18etw6VUnF",
      "ticker": "EMC2"
    },
    {
      "address": "RDbAXLCmQ2EN7daEZZp7CC9xzkcN8DfAZd",
      "ticker": "LABS"
    },
    {
      "address": "RDbAXLCmQ2EN7daEZZp7CC9xzkcN8DfAZd",
      "ticker": "COQUI"
    },
    {
      "address": "15JySpKUoCRo3dD36Ppz6fpmEV9mSDFjSf",
      "ticker": "BCH"
    },
    {
      "address": "GN9trweRn43686WL2LV6XSAf9ewcRCFbZY",
      "ticker": "GIN"
    },
    {
      "address": "XezpH4yNkuePCZocxH9CxCWZ4pjTVm34QH",
      "ticker": "DASH"
    },
    {
      "address": "LPXvi2dJsrfrJRuCGXpHNgtXShX3YctTVm",
      "ticker": "LTC"
    },
    {
      "address": "MztLeTpTiaXMaATYND9ZKByfxiYpMDsRXJ",
      "ticker": "NMC"
    },
    {
      "address": "D9T4z5G86cL5adPdpypYeRzN7ct4kGn9hQ",
      "ticker": "DGB"
    }
  ]
}
```

## mm2 setprice

The setprice method places an order on the orderbook, and it relies on this node acting as a maker, also called a Bob node.

**URL**: `/api/v1/legacy/mm2/setprice`

**Method**: `POST`

**Auth required**: No

**Permissions required**: None

### Success Response

**Code** `200 OK`

**Content examples (request)**

```json
{
  "base": "RICK",
  "method": "setprice",
  "price": "1",
  "rel": "MORTY",
  "userpass": "YOUR_PASSWORD_HERE",
  "volume": "1"
}
```

**Content example (answer)**

```json
{
  "result": {
    "base": "RICK",
    "created_at": 1566505487524,
    "matches": {},
    "max_base_vol": "1",
    "min_base_vol": "0",
    "price": "1",
    "rel": "MORTY",
    "started_swaps": [],
    "uuid": "de05f451-d665-45c6-9526-112446644621"
  }
}
```

### Error Response

**Code**: `400 Bad request` (Ill-formed request)

**Code**: `500 Internal Server Error` (`mm2` return 500 error code + message)

## mm2 cancel_order

The `cancel_order` cancels the active order created by the MM2 node.

**URL**: `/api/v1/legacy/mm2/cancel_order`

**Method**: `POST`

**Auth required**: No

**Permissions required**: None

### Success Response

**Code** `200 OK`

**Content examples (request)**

```json
{
  "method": "cancel_order",
  "userpass": "YOUR_PASSWORD_HERE",
  "uuid": "de05f451-d665-45c6-9526-112446644621"
}
```

**Content example (answer)**

```json
{
  "result": "success"
}
```

### Error Response

**Code**: `400 Bad request` (Ill-formed request)

**Code**: `500 Internal Server Error` (`mm2` return 500 error code + message)

## mm2 buy

The buy method issues a buy request and attempts to match an order from the orderbook based on the provided arguments.

**URL**: `/api/v1/legacy/mm2/buy`

**Method**: `POST`

**Auth required**: No

**Permissions required**: None

### Success Response

**Code** `200 OK`

**Content examples (request)**

```json
{
  "base": "RICK",
  "method": "buy",
  "price": "1",
  "rel": "MORTY",
  "userpass": "YOUR_PASSWORD_HERE",
  "volume": "1"
}
```

**Content example (answer)**

```json
{
  "result": {
    "action": "Buy",
    "base": "RICK",
    "base_amount": "1",
    "dest_pub_key": "0000000000000000000000000000000000000000000000000000000000000000",
    "method": "request",
    "rel": "MORTY",
    "rel_amount": "1",
    "sender_pubkey": "9df6d7fa49c31959fce388bb8e8065fd3d9ace5bc4bbafd0cbd4c6604492670a",
    "uuid": "89001dbe-cec6-4be0-a030-f48e8bab2d96"
  }
}
```

### Error Response

**Code**: `400 Bad request` (Ill-formed request)

**Code**: `500 Internal Server Error` (`mm2` return 500 error code + message)

## mm2 withdraw

This method generates a raw transaction which should then be broadcast using send_raw_transaction.

**URL**: `/api/v1/legacy/mm2/withdraw`

**Method**: `POST`

**Auth required**: No

**Permissions required**: None

### Success Response

**Code** `200 OK`

**Content examples (request)**

```json
{
  "amount": "0.001",
  "coin": "RICK",
  "method": "withdraw",
  "to": "RDbAXLCmQ2EN7daEZZp7CC9xzkcN8DfAZd",
  "userpass": "YOUR_PASSWORD_HERE"
}
```

**Content example (answer)**

```json
{
  "tx_hex": "0400008085202f89017b4586055138584f81eff4427180e47a7b6ade64bb12eadd60aba1975d0ba50d000000006a47304402207f747b7e853e3e6fe6f3f3c6ac994d0365b741a6c99da27e1925121cdc76313002207936392b67b49047b5c129306ecb06e82ec4b36754e5bfbed2a8da6f7123bacb0121029df6d7fa49c31959fce388bb8e8065fd3d9ace5bc4bbafd0cbd4c6604492670affffffff02a0860100000000001976a9142f46b1468c017ebffcb99043143049b16393be7488ac9052f405000000001976a9142f46b1468c017ebffcb99043143049b16393be7488ac9a75a05d000000000000000000000000000000",
  "tx_hash": "8f7a417d45e4df17d15f04fd8072a7d340b2fb3e377ad0846679364753900eec",
  "from": [
    "RDbAXLCmQ2EN7daEZZp7CC9xzkcN8DfAZd"
  ],
  "to": [
    "RDbAXLCmQ2EN7daEZZp7CC9xzkcN8DfAZd"
  ],
  "total_amount": "0.99999",
  "spent_by_me": "0.99999",
  "received_by_me": "0.99998",
  "my_balance_change": "-0.00001",
  "block_height": 0,
  "timestamp": 1570796954,
  "fee_details": {
    "amount": "0.00001"
  },
  "coin": "RICK",
  "internal_id": ""
}
```

### Error Response

**Code**: `400 Bad request` (Ill-formed request)

**Code**: `500 Internal Server Error` (`mm2` return 500 error code + message)

## mm2 send_raw_transactionn

**URL**: `/api/v1/legacy/mm2/send_raw_transaction`

**Method**: `POST`

**Auth required**: No

**Permissions required**: None

### Success Response

**Code** `200 OK`

**Content examples (request)**

```json
{
  "coin": "RICK",
  "method": "send_raw_transaction",
  "tx_hex": "0400008085202f8902b59470055506b34765ab24d21647da4287ecb9c1bc0904e76668bf86f51ab741000000006a4730440220728a3ce6245481f36c562144f6081705f13bffa51b2e22585d2269fc10b6cac202206d7510cf3d57d8e75f6ea294c36361564278b2cd7c55cb4fdc0e2fa84ad9a5b60121029df6d7fa49c31959fce388bb8e8065fd3d9ace5bc4bbafd0cbd4c6604492670affffffffb59470055506b34765ab24d21647da4287ecb9c1bc0904e76668bf86f51ab741010000006b4830450221009c1bf21bc533b91c8d7583045be1ff7361e826d020955ae19725aaa8b017408e022066b8998c518618b522ad0b05dc1954efc38b680655c7ec90eb0eb42a46d4f6670121029df6d7fa49c31959fce388bb8e8065fd3d9ace5bc4bbafd0cbd4c6604492670affffffff02a0860100000000001976a9142f46b1468c017ebffcb99043143049b16393be7488aca84ef405000000001976a9142f46b1468c017ebffcb99043143049b16393be7488ac6886a15d000000000000000000000000000000",
  "userpass": "YOUR_PASSWORD_HERE"
}
```

**Content example (answer)**

```json
{"tx_hash":"0a299168d2d6b056151dcb969dae47927f0daf8c9b64a7bd902e90ebda9cee92"}
```

### Error Response

**Code**: `400 Bad request` (Ill-formed request)

**Code**: `500 Internal Server Error` (`mm2` return 500 error code + message)

## mm2 sell

The sell method issues a sell request and attempts to match an order from the orderbook based on the provided arguments.

**URL**: `/api/v1/legacy/mm2/sell`

**Method**: `POST`

**Auth required**: No

**Permissions required**: None

### Success Response

**Code** `200 OK`

**Content examples (request)**

```json
{
  "base": "RICK",
  "method": "sell",
  "price": "1",
  "rel": "MORTY",
  "userpass": "YOUR_PASSWORD_HERE",
  "volume": "1"
}
```

**Content example (answer)**

```json
{
  "result": {
    "action": "Sell",
    "base": "RICK",
    "base_amount": "1",
    "dest_pub_key": "0000000000000000000000000000000000000000000000000000000000000000",
    "method": "request",
    "rel": "MORTY",
    "rel_amount": "1",
    "sender_pubkey": "9df6d7fa49c31959fce388bb8e8065fd3d9ace5bc4bbafd0cbd4c6604492670a",
    "uuid": "89001dbe-cec6-4be0-a030-f48e8bab2d96"
  }
}
```

### Error Response

**Code**: `400 Bad request` (Ill-formed request)

**Code**: `500 Internal Server Error` (`mm2` return 500 error code + message)

## mm2 cancel_all_orders

The cancel_all_orders cancels the active orders created by the MM2 node by specified condition.

**URL**: `/api/v1/legacy/mm2/cancel_all_orders`

**Method**: `POST`

**Auth required**: No

**Permissions required**: None

### Success Response

**Code** `200 OK`

**Content examples (request)**

```json
{
  "cancel_by": {
    "type": "All"
  },
  "method": "cancel_all_orders",
  "userpass": "YOUR_PASSWORD_HERE"
}
```

**Content example (answer)**

```json
{
  "result": {
    "cancelled": [
      "25366927-d48b-4aca-b950-f81c40c36c83"
    ],
    "currently_matching": []
  }
}
```

### Error Response

**Code**: `400 Bad request` (Ill-formed request)

**Code**: `500 Internal Server Error` (`mm2` return 500 error code + message)

## SM getstrategy

The cancel_all_orders cancels the active orders created by the MM2 node by specified condition.

**URL**: `/api/v1/sm/getstrategy`

**Method**: `POST`

**Auth required**: No

**Permissions required**: None

### Success Response

**Code** `200 OK`

**Content examples (request)**

```json
{
  "pair" : {
    "base" : "BTC",
    "quote" : "ETH"
  }
}
```

**Content example (answer)**

```json
{
  "pair" : {
    "base" : "BTC",
    "quote" : "ETH"
  },
  "spread" : 0.1,
  "quantity" : 5,
  "both" : true
}
```

### Error Response

**Code**: `400 Bad request` (Ill-formed request)

**Code**: `500 Internal Server Error` (`sm` return 500 error code + message)

## SM addstrategy

The cancel_all_orders cancels the active orders created by the MM2 node by specified condition.

**URL**: `/api/v1/sm/addstrategy`

**Method**: `POST`

**Auth required**: No

**Permissions required**: None

### Success Response

**Code** `200 OK`

**Content examples (request)**

```json
{
  "pair" : {
    "base" : "BTC",
    "quote" : "ETH"
  },
  "spread" : 0.1,
  "quantity" : 5,
  "both" : true
}
```

**Content example (answer)**

```json
{
  "result": "success"
}
```

### Error Response

**Code**: `400 Bad request` (Ill-formed request)

**Code**: `500 Internal Server Error` (`sm` return 500 error code + message)
