dataMagnetometer = [dataSensors(1:end, 1), dataSensors(1:end, 2)];

dataMagnetometerX = [dataSensors(1:end, end)/1000 dataSensors(1:end, 1)];
dataMagnetometerY = [dataSensors(1:end, end)/1000 dataSensors(1:end, 2)];

plot(dataSensors(1:end, end)/1000, -(dataMagnetometerX ./ dataMagnetometerY))
hold on
plot(dataSensors(1:end, end)/1000, tan(dataSensors(1:end, 4).*pi/180))

% plot(dataMagnetometrX(1:end, 1), dataMagnetometrX(1:end, 2));

% plot(dataMagnetometerX(1:end, 1), atan2(dataSensors(1:end, 1), dataSensors(1:end, 2)) * 180 / pi);
grid on;
% getAngleMagnetometer(dataMagnetometer)