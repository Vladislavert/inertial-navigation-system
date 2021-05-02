indxGyro = 3; % значение индекса под которым начинаются измерения гироскопа
indxMagnet = 6; % значение индекса под которым начинаются измерения магнитометра
indxAcc = 0; % значение индекса под которым начинаются измерения акселерометра
indxTime = 12; % значение индекса под которым начинаются измерения времени
indxOrient = 9; % значение индекса под которым начинаются измерения ориентации



dataGyroscope = [dataSensors(1:end, indxGyro), dataSensors(1:end, indxGyro + 1), dataSensors(1:end, indxGyro + 2)];

dataGyroscopeX = [dataSensors(1:end, end)/1000 dataSensors(1:end, 1)];
dataGyroscopeY = [dataSensors(1:end, end)/1000 dataSensors(1:end, 2)];

plot(dataSensors(1:end, end)/1000, -(dataGyroscopeX  ./ dataGyroscopeY))
hold on
plot(dataSensors(1:end, end)/1000, tan(dataSensors(1:end, indxOrient + 1).*pi/180))

% plot(dataMagnetometrX(1:end, 1), dataMagnetometrX(1:end, 2));

% plot(dataMagnetometerX(1:end, 1), atan2(dataSensors(1:end, 1), dataSensors(1:end, 2)) * 180 / pi);
grid on;
% getAngleMagnetometer(dataMagnetometer)