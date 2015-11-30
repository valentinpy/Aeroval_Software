# Flashing script
# Valentin Py - Aeroval
# 02.11.15

#You can run this file with bash after having compiled the project, in order to flash the microcontroller.
#You should myabe modify gdb_flash.txt

#Lanch the server
JLinkGDBServer &

#Lauch the client with the file-specified parameters
arm-none-eabi-gdb -x gdb_flash.txt
