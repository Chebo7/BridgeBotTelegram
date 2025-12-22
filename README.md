## Statistics:
[![Ask DeepWiki](https://deepwiki.com/badge.svg)](https://deepwiki.com/Chebo7/BridgeBotTelegram)
![GitHub code size](https://img.shields.io/github/languages/code-size/Chebo7/BridgeBotTelegram)
![Last Commit](https://img.shields.io/github/last-commit/Chebo7/BridgeBotTelegram)
![GitHub Commits](https://img.shields.io/github/commit-activity/m/Chebo7/BridgeBotTelegram)
![CMake](https://img.shields.io/badge/CMake-3.30+-blue.svg)


![GitHub Stars](https://img.shields.io/github/stars/Chebo7/BridgeBotTelegram)
![GitHub Forks](https://img.shields.io/github/forks/Chebo7/BridgeBotTelegram)
![GitHub Watchers](https://img.shields.io/github/watchers/Chebo7/BridgeBotTelegram)
![GitHub](https://img.shields.io/github/license/Chebo7/BridgeBotTelegram)
![GitHub language count](https://img.shields.io/github/languages/count/Chebo7/BridgeBotTelegram)

# A simple and effective Telegram bot for receiving and forwarding user messages to the administrator. Ideal for personal contacts or support.

## Install

You must have the boost library, cmake, and make downloaded.

Make project:
```
git clone https://github.com/Chebo7/BridgeBotTelegram.git
cd BridgeBotTelegram
mkdir build
cd build
cmake ..
make -j
```

Next, we configure the environment variables:
``` 
export TELEGRAM_BOT_TOKEN="Your token"
```
and 

```
export ADMIN_CHAT_ID="Your Telegram ID"
```

## Launch:
```
./tgbot &
```
