This project must run our of the box for STM32CubeIde. If it doesn't run there may be problem with System parameters settings or missing files from the compiler classpath.

Look at recommneded settings present in ProjectSettings Folder. There are timing related problems at mulriple places in the project, timing code needs to be improved-

Timeout logic used doesn't work everytime and sometimes it timeout faster than needed. This results in resetting the Source again and again.
 # usbpd_fusb302
# usbpd_fusb302
# usbpd_fusb302
