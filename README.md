[//]: # (Main image, centered)
<p align="center">
  <img width="300" src="https://raw.githubusercontent.com/GTeamx/.github/main/assets/dynamic-chat.png">
</p>

[//]: # (Main title, centered)
<h1 align="center">🌐 Dynamic.Chat 🌐</h1>

[//]: # (Shield.io badges, main basic stuff, centered)
<div align="center">

  <a href="">![GitHub Release](https://img.shields.io/github/v/release/GTeamx/Dynamic.Chat?sort=date&display_name=tag&style=for-the-badge&label=Latest%20Release&color=55FFFF)</a>
  <a href="">![GitHub Downloads (all assets, latest release)](https://img.shields.io/github/downloads/GTeamx/Dynamic.Chat/latest/total?sort=date&style=for-the-badge&label=Latest%20Downloads)</a>
  <a href="">![GitHub Downloads (all assets, all releases)](https://img.shields.io/github/downloads/GTeamx/Dynamic.Chat/total?style=for-the-badge&label=Total%20Downloads)</a>
  <a href="">![GitHub License](https://img.shields.io/github/license/GTeamx/Dynamic.Chat?style=for-the-badge)</a>
  <br>
  <a href="">![GitHub commits since latest release](https://img.shields.io/github/commits-since/GTeamx/Dynamic.Chat/latest?sort=date&style=for-the-badge&label=commits%20since%20release)</a>
  <a href="">![GitHub commit activity (branch)](https://img.shields.io/github/commit-activity/m/GTeamx/Dynamic.Chat/dev?style=for-the-badge&label='dev'%20branch%20commits)</a>
  <a href="">![GitHub commits difference between two branches/tags/commits](https://img.shields.io/github/commits-difference/GTeamx/Dynamic.Chat?base=main&head=dev&style=for-the-badge&label='dev'%20ahead%20of%20'main'%20in%20commits)</a>
  <br>
  <a href="">![GitHub branch check runs](https://img.shields.io/github/check-runs/GTeamx/Dynamic.Chat/main?style=for-the-badge&label='main'%20branch%20checks)</a>
  <a href="">![GitHub branch check runs](https://img.shields.io/github/check-runs/GTeamx/Dynamic.Chat/dev?style=for-the-badge&label='dev'%20branch%20checks)</a>
  <a href="">![Static Badge](https://img.shields.io/badge/Dependencies-None-green?style=for-the-badge)</a>
  <br>
  <a href="">![GitHub Repo stars](https://img.shields.io/github/stars/GTeamx/Dynamic.Chat?style=for-the-badge)</a>
  <a href="">![GitHub watchers](https://img.shields.io/github/watchers/GTeamx/Dynamic.Chat?style=for-the-badge)</a>
  <a href="">![GitHub forks](https://img.shields.io/github/forks/GTeamx/Dynamic.Chat?style=for-the-badge)</a>
  <a href="">![Discord](https://img.shields.io/discord/1046001788106575912?style=for-the-badge&label=Discord)</a>
  
</div>

Dynamic.Chat aims to be an easy to use efficient and secure LAN chatting system. Using a brute-force oriented security (XOR encryption) with a user defined encryption key, broadcasted UDP messages to prevent tracing down who receives the message and who doesn't.
*This Dyanmic product is part of Dynamic.\* products line*

## ⬇️ Usage

Simply download the latest release (with your prefered language, French or English) and simply double click the exe file!

## 🌟 Features & Functionalities

- Send encrypted messages over a LAN network
- Send/receive messages from different clients
- XOR + Password encryption
- Change encryption key
- Add other users encryption keys
- Change broadcast address

## 🤔 How does it work ?

- Client side (send):
  When starting Dynamic.Chat an encryption key is created using the current Windows session's username and the current seconds (time).
  That encryption key is saved and used to encrypt outgoing messages using a XOR encryption.
  After the message is encrypted, its broadcasted on port 888/UDP on a LAN scale.

- Server side (receive):
  When starting Dynamic.Chat the listening server is started on a new thread an runs in the background.
  It listens to all available addresses on port 888/UDP.
  When receiving a message on that port, it will try and decrypt the packet's messages using the provided encryption keys (using 'addmdp').
  If the decryption succeeds, the beginning of the message will start with "IDENT=thekeyusedtodecrypt" which confirms that the message has been decrypted correctly.
  After the decryption succeeded, the sender's username is extract from the packet's message in the field "USER=senderusername". The username is defined based on the sender's Windows session username.
  Finally we extract the message and format it in the following format "current time | sender's username: sender's message", the message is then displayed to the console.

## 🔔 Releases/Updates

We highly recommand using the latest releases when possible as they might fix critical issues or errors. **Dynamic.Chat updates are ONLY RELEASED [HERE](https://github.com/GTeamx/Dynamic.Chat)!**.

There a high chance you'll face errors and issues if your using the latest .exe file from the dev or main branch, please only use the released versions.

## 🚷 Errors/Bugs (Issues)

If you face any error or bugs during the usage of Dynamic.Chat, please open an issue on our GitHub page. Providing sufficiant information to we are able to reproduce the error/issue on our side (provide the OS, released version that you were using, any "special" config changes that may or may not have done like in the network interfaces for example, ect...)

## 🔃 Contributing

Before contributing, please make sure that you follow our conventions (naming scheme, indentation) and that your code works! Make sure to also precise on what OS and what OS version you test were ran.

## 📜 License

This project is licensed under GNU General Public License v3.0 (GPL).
