#include <iostream>
#include <fstream>

#include "binance-cpp-api.hpp"
#include "binance-cpp-api-http.hpp"
#include "binance-cpp-api-websocket.hpp"

int main(int argc, char **argv) {
    std::cout << "start binance cpp api general step 2 test!" << std::endl;
    binance_api::BinanceApi binanceapi;
    binance_api::Settings settings(argc, argv);
    if(settings.is_error) {
        std::cout << "Settings error!" << std::endl;
        return EXIT_FAILURE;
    }
    settings.demo = true;

    /* инициализируем основные настройки */
    binanceapi.init_main(settings);

    binance_api::CandlestickStreams candlestick_streams(true);
    candlestick_streams.add_symbol_stream("BTCUSDT", 1);
    candlestick_streams.add_symbol_stream("ETCUSDT", 1);
    candlestick_streams.add_symbol_stream("LTCUSDT", 1);
    candlestick_streams.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(20000));
    std::cout << "offset timestamp: " << candlestick_streams.get_offset_timestamp() << std::endl;
    std::cout << "BTCUSDT candle close: " << candlestick_streams.get_candle("BTCUSDT", 1).close << std::endl;
    std::cout << "ETCUSDT candle close: " << candlestick_streams.get_candle("ETCUSDT", 1).close << std::endl;
    const double quantity = 1;

    /* открываем ордер */
    if(true){
        int err = binanceapi.open_order(
            "BTCUSDT",
            binance_api::TypesPositionSide::LONG,
            settings.position_mode,
            quantity,
            candlestick_streams.get_candle("BTCUSDT", 1).close + 5,
            candlestick_streams.get_candle("BTCUSDT", 1).close - 5,
            60,
            false,
            settings.recv_window);
        std::cout << "BTCUSDT open_order code: " << err << std::endl;
    }
    if(true){
        int err = binanceapi.open_order(
            "ETCUSDT",
            binance_api::TypesPositionSide::SHORT,
            settings.position_mode,
            quantity,
            candlestick_streams.get_candle("ETCUSDT", 1).close - 0.01,
            candlestick_streams.get_candle("ETCUSDT", 1).close + 0.01,
            60 + xtime::get_timestamp(),
            true,
            settings.recv_window);
        std::cout << "ETCUSDT open_order code: " << err << std::endl;
    }

    std::system("pause");
    return 0;
}
