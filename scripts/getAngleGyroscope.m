% /* ***************************************************************************************************   */
% /* 	|Author: Vladislavert         |ssssssssssssssso++——+++osssssssssssssssssssssssssssssssssssssssss|  */
% /* 	|e-mail: chuvarevan@mail.ru   |yyyysoooooo..   /   |    ./yyyyyyyyyyosshhhhhyyyyyyyyyyyyyyyyyyyy|  */
% /* 	|_____________________________|yyyyyyysssso////  /syyyyyyyyyyyyyyy0    /yhhhhhyyyyyyyyyyyyyyyyyy|  */
% /*	|ssysyyyyysssyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyso+   /ssyyyyyyyyyyyyso    0yhhhhhhhhyhyyyyyyyyyyyyyy|  */
% /*	|syyyyyys+.     ++osy      ...sssoosssssssoo+ +o/osssyyyyso+//s/ /oyyyhyhhhhhhhyyyyyyyyyyyyyyyyy|  */
% /*	|syyyyyysooo+/::/+/  ++++oooo+++ooooosssssshhyyyyyooo+//+oo++/ /:os+++++++++++++yyhhhyyyyyyyyyyy|  */
% /*	|ssssyyyyyys+/    ///////yyyyyys:--::/syo+//:/::::::/ooo+///  /oys\.          /ossyyyyyyyyyy'sss|  */
% /*	|yyyyyysyys/    ::://///////::/:------+s/::----::::::::/:-//+osssyyyyyyyss+/::://o ..........+ss|  */
% /*	|syyyyyyyso/   :ooooooooo---/-----::---:::----::::--:/----://+oooossyyhhhhhy/::::  :oyyyyyyyyyyy|  */
% /*	|yyysyyyyso+ +++/:ooooooo--/-0----/-/-----::::::::.-::::----+/:::::///++++++|     ////shhhhyyyyy|  */
% /*	|ysyyyyyysssossss+/:+oooo:|-00---/-0-..-----.-:---.-------::: ++++++++++//:::/   //::/oyhyyyyyyy|  */
% /*	|syyyyyysssssyyyo+/osssss+-\-0-:|-00.....--...-//:.----::      ssooooooossso+//  ::/+ooyyyyyyyyy|  */
% /*	|yyyyyyssssyyyyso+ssyyyyys+::-\+-\-0---.----..://+o::::-      /sysso+ossooooo++/  //+oosssssysss|  */
% /*	|yyyyyysssyyyyyoosyyyyyyyyyss+--/--------:----:::::::     ///sssssssyssoosoooo\ +++ossyyysyyyyyy|  */
% /*	|ysyyyysyyyyyysssyyyyyyysssso+::::--::/+++/://::://+     ::+osyyhhhyysssssssssso+oossssyyyyyyyyy|  */
% /*	|sssyysyyyyyyyyyyyyyyyyyysssoooo++/++++oooo+++////////\::::/+osyyhhyhyyyssssyyssooosyyyyyyyyyyyy|  */
% /*	|sysyysyyyyyyyyyyyyyyyyyyyyssosoo++++o+oo++///::::|::::::|::::: +osyyhyyssssyyyyyysssyhhhyyyyyyy|  */
% /*	╔═══╦═══╦═══╦══╦══╗yyyyyysyo////\                  \---/-        /+syyyssssyyyyhhyysyyyhyyyyyyyy|  */
% /*	║╔═╗║╔══╣╔══╩╗╔╣╔═╣╗─╔══╦══╗oooooooooo++++o+++/:::/:::/++         /oyyyyssyyhhhhhyhhyhhhyyyyyyyy|  */
% /*	║╚═╝║╚══╣║╔═╗║║║╚═╣║─║╔╗║╔╗║yysyyyso+++ssosoo+o+/::::::-:+ooo+        syyyyyyyhhyhhhhyyyyyyyyyyy|  */
% /*	║╔╗╔╣╔══╣║╚╗║║║╚═╗║║─║╚╝║╚╝╚╗yyyssssoosoo++++++++:---:--:+oossso       oyysyyhhhhhhhhyhhyyhhyyyy|  */
% /*	║║║║║╚══╣╚═╝╠╝╚╦═╝║╚═╣╔╗║ ═ ║ysyysssssoooooooo++++:----::+oossysso++    oyyhyyhhyhyyhyhyyhyhyyyy|  */
% /*	╚╝╚╝╚═══╩═══╩══╩══╩══╩╝╚╩═══╝yyysssssooooo++++++//:---:/++oosssssysss+: osyhhhyhhyyhyyyyyyyyyyyy|  */
% /* ***************************************************************************************************   */

indxGyro = 4; % значение индекса под которым начинаются измерения гироскопа
indxMagnet = 7; % значение индекса под которым начинаются измерения магнитометра
indxAcc = 1; % значение индекса под которым начинаются измерения акселерометра
indxTime = 13; % значение индекса под которым начинаются измерения времени
indxOrient = 10; % значение индекса под которым начинаются измерения ориентации



dataGyroscope = [dataSensors(1:end, indxGyro), dataSensors(1:end, indxGyro + 1), dataSensors(1:end, indxGyro + 2)];

dataGyroscopeX = [dataSensors(1:end, indxGyro)];
dataGyroscopeY = [dataSensors(1:end, indxGyro + 1)];
dataGyroscopeZ = [dataSensors(1:end, indxGyro + 2)];
% hold off
% lot(dataSensors(1:end, end)/1000, dataGyroscopeZ)
% figure
% значение угловой скорости по трём осям
subplot(3, 1, 1)
plot(dataSensors(1:end, end)/1000, rad2deg(dataGyroscopeX))
title("Данные об угловых скоростях полученных с гироскопа")
legend("Значение в градусах/сек по тангажу")
subplot(3, 1, 2) 
plot(dataSensors(1:end, end)/1000, rad2deg(dataGyroscopeY))
legend("Значение в градусах/сек по крену")
subplot(3, 1, 3)
plot(dataSensors(1:end, end)/1000, rad2deg(dataGyroscopeZ))
legend("Значение в градусах/сек по рысканью")


% интегрирование методом Эйлера

% начальное значение
angleGyroscopeX(1) = deg2rad(dataSensors(1, indxOrient + 1)); % угол тангажа
angleGyroscopeY(1) = deg2rad(dataSensors(1, indxOrient + 2)); % угол крена
angleGyroscopeZ(1) = deg2rad(dataSensors(1, indxOrient)); % угол рысканья
for i = 2:size(dataSensors(1:end, 2))
    angleGyroscopeX(i) = angleGyroscopeX(i - 1) + dataGyroscopeX(i - 1)*(dataSensors(i, end) - dataSensors(i - 1, end))/1000;
    angleGyroscopeY(i) = angleGyroscopeY(i - 1) + dataGyroscopeY(i - 1)*(dataSensors(i, end) - dataSensors(i - 1, end))/1000;
    angleGyroscopeZ(i) = angleGyroscopeZ(i - 1) + dataGyroscopeZ(i - 1)*(dataSensors(i, end) - dataSensors(i - 1, end))/1000;
end
% отрисовка получившихся значений
figure
subplot(3, 1, 1)
plot(dataSensors(1:end, end)/1000,  rad2deg(angleGyroscopeX))
title("Данные об углах полученных с гироскопа")
legend("Значение в градусах по тангажу")
grid on
subplot(3, 1, 2)
plot(dataSensors(1:end, end)/1000,  rad2deg(angleGyroscopeY))
legend("Значение в градусах по крену")
grid on
subplot(3, 1, 3)
plot(dataSensors(1:end, end)/1000,  rad2deg(angleGyroscopeZ))
legend("Значение в градусах по рысканью")
grid on



% hold on
% plot(dataSensors(1:end, end)/1000, tan(dataSensors(1:end, indxOrient + 1).*pi/180))

% plot(dataMagnetometrX(1:end, 1), dataMagnetometrX(1:end, 2));

% plot(dataMagnetometerX(1:end, 1), atan2(dataSensors(1:end, 1), dataSensors(1:end, 2)) * 180 / pi);

% getAngleMagnetometer(dataMagnetometer)