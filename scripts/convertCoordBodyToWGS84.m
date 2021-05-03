%% для получения информации введите команду >> help
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
% latitude(широта)
% Longitude(долгота)
% Altitude(высота)
% Значение углов ориентации во время начальной выставки БИНС
% Azimuth(Азимут)
% Pitch(Тангаж)
% Roll(Крен)

% определение положение в WGS-84
% 1. Накопить позицию по GPS(провести начальную выставку, в том числе БИНС)
% для дальнейшего перевода из стартовой СК в ГСК
% 2. Перевод из ССК в связанные нормальные оси(СНС) с помощью матрицы
% повротов, для определение позиции в стартовой СК
% 3. Перевод из стартовой СК в геоцентрическую СК(WGS-84) с помощью
% сложения

%%
% положение в WGS-84
% latitude(широта) = 55.814068
% Longitude(долгота) = 37.50038
% Altitude(высота) = 210.7
% Значение углов ориентации во время начальной выставки БИНС
% Azimuth(Азимут) = 320.0798
% Pitch(Тангаж) = 0.6876
% Roll(Крен) = -1.9878

%%
coordinateWGS = [55.814068, 37.50038, 210.7];

%angl = [0*pi/180; 90*pi/180; 45*pi/180];
angl = [0*pi/180; -1.46; 0.313];

            R = [cos(angl(3))*cos(angl(2)), sin(angl(1))*sin(angl(3))*cos(angl(2))-cos(angl(1))*sin(angl(2)), cos(angl(1))*sin(angl(3))*cos(angl(2))+sin(angl(1))*sin(angl(2));...
                 cos(angl(3))*sin(angl(2)), sin(angl(1))*sin(angl(3))*sin(angl(2))+cos(angl(1))*cos(angl(2)), cos(angl(1))*sin(angl(3))*sin(angl(2))-sin(angl(1))*cos(angl(2));...
                 -sin(angl(3))                                       , sin(angl(1))*cos(angl(3))                                        , cos(angl(1))*cos(angl(3))] ;
Vector = [0;0;4.28];
Rotation = R*Vector

plot3([0,Vector(1)],[0,Vector(2)],[0,Vector(3)])
hold on
plot3([0,Rotation(1)],[0,Rotation(2)],[0,Rotation(3)])
xlabel('x')
ylabel('z')
zlabel('y')
















