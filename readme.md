# nodeMCU RFID Relay Dengan Telegram Notif

Ini merupakan IoT berbasis NodeMCU v3 yang di buat untuk menyalakan suatu alat elektronik menggunakan modul relay yang harus ter autentikasi dengan modul RFID

> Cara Kerja Dari alat ini sebagai berikut:
> Modul RFID akan stand by dan mengscan kartu yang di dekatkan ke RFID
> kemudian modul akan memberi tahu ke main board (NODEMCU) menggunakan komunikasi serial SPI
> jika ID pada kartu di RFID betul, maka relay akan nyala dan mengirimkan notif ke group telegram
> jika ID pada kartu di RFID salah, maka alat akan mengirimkan notif warning ke group telegram

# Alat Dan Bahan
  - Board NodeMCU v3
  - Modul RFID MFRC522
  - Modul Relay 3V
  - Kabel Jumper (F/F)
