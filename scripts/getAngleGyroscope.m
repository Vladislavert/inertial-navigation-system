indxGyro = 4; % значение индекса под которым начинаются измерения гироскопа
indxMagnet = 7; % значение индекса под которым начинаются измерения магнитометра
indxAcc = 1; % значение индекса под которым начинаются измерения акселерометра
indxTime = 13; % значение индекса под которым начинаются измерения времени
indxOrient = 10; % значение индекса под которым начинаются измерения ориентации



dataGyroscope = [dataSensors(1:end, indxGyro), dataSensors(1:end, indxGyro + 1), dataSensors(1:end, indxGyro + 2)];

dataGyroscopeX = [dataSensors(1:end, indxGyro)];
dataGyroscopeY = [dataSensors(1:end, indxGyro + 1)];
dataGyroscopeZ = [dataSensors(1:end, indxGyro + 2)];
hold off
plot(dataSensors(1:end, end)/1000, dataGyroscopeZ)
% проинтегриованные значения с гироскопа
figure
plot(dataSensors(1:end, end)/1000, cumtrapz(dataGyroscopeZ, rad2deg(dataSensors(1:end, end)/1000)))

% интегрирование методом Эйлера

% начальное значение
angleGyroscope(1) = deg2rad(dataSensors(1, indxOrient)); % угол рысканья
for i = 2:size(dataSensors(1:end, 2))
    angleGyroscope(i) = angleGyroscope(i - 1) + dataGyroscopeZ(i - 1)*(dataSensors(i, end) - dataSensors(i - 1, end))/1000;
%     angleGyroscope(i) = angleGyroscope(i - 1) + 0.6*(dataSensors(i, end) - dataSensors(i - 1, end))/1000;
end
% отрисовка получившихся значений
figure
plot(dataSensors(1:end, end)/1000,  rad2deg(angleGyroscope))


% hold on
% plot(dataSensors(1:end, end)/1000, tan(dataSensors(1:end, indxOrient + 1).*pi/180))

% plot(dataMagnetometrX(1:end, 1), dataMagnetometrX(1:end, 2));

% plot(dataMagnetometerX(1:end, 1), atan2(dataSensors(1:end, 1), dataSensors(1:end, 2)) * 180 / pi);
grid on;
% getAngleMagnetometer(dataMagnetometer)