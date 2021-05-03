dataMagnetometer = [dataSensors(1:end, indxMagnet), dataSensors(1:end, indxMagnet + 1)];

dataMagnetometerX = [dataSensors(1:end, end)/1000 dataSensors(1:end, indxMagnet)];
dataMagnetometerY = [dataSensors(1:end, end)/1000 dataSensors(1:end, indxMagnet + 1)];

plot(dataSensors(1:end, end)/1000, -(dataMagnetometerX ./ dataMagnetometerY))
hold on
% plot(dataSensors(1:end, end)/1000, tan(dataSensors(1:end, indxOrient).*pi/180))
% получение угла ориентации в градусах
plot(dataSensors(1:end, end)/1000, (dataSensors(1:end, indxOrient)))

% plot(dataMagnetometrX(1:end, 1), dataMagnetometrX(1:end, 2));

% plot(dataMagnetometerX(1:end, 1), atan2(dataSensors(1:end, 1), dataSensors(1:end, 2)) * 180 / pi);
grid on;
% getAngleMagnetometer(dataMagnetometer)