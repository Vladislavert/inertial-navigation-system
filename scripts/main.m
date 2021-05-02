dataMagnetometer = [dataSensors(1:end, 1), dataSensors(1:end, 2)];

dataMagnetometrX = [dataSensors(1:end, end)/1000 dataSensors(1:end, 1)];
dataMagnetometrY = [dataSensors(1:end, end)/1000 dataSensors(1:end, 2)];

% plot(dataMagnetometrX(1:end, 1), dataMagnetometrX(1:end, 2));

plot(dataMagnetometrX(1:end, 1), atan2(dataSensors(1:end, 1), dataSensors(1:end, 2)) * 180 / pi);

% getAngleMagnetometer(dataMagnetometer)

