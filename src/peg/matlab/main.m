clearvars;

rootPath = '~/logPegShape/ineq2/';
robotName = 'g500_A/';
taskName = 'ARM_SHAPE';

plotTask(rootPath, robotName, taskName);

%% plot yDots (command sent to robot)
legFontSize = 13;
titleFontSize = 16;
ylabFontSize = 15;


yDot = importMatrices(strcat(rootPath, robotName, '/yDot.txt'));
nRow = size(yDot, 1);
nStep = size(yDot, 3);

%millisecond indicated in missionManager
sControlLoop = 0.1;
totSecondPassed = sControlLoop*(nStep-1);
seconds = 0:sControlLoop:totSecondPassed;

% plot joint commands
figure
hold on;
for i = 1:4
    a(:) = yDot(i,1,:);
    plot(seconds, a);
end
xlabel('time [s]');
leg = legend('$\dot{q}_1$','$\dot{q}_2$', '$\dot{q}_3$', '$\dot{q}_4$');
ylab = ylabel('Joint command [rad/s]');
tq = title(strcat(robotName, 'Joint command sent (yDot[1:4])'));
set(leg, 'Interpreter', 'latex', 'FontSize' , legFontSize);
set (tq, 'Interpreter', 'none', 'FontSize' , titleFontSize);
set (ylab, 'Interpreter', 'none', 'FontSize', ylabFontSize);
hold off

%plot vehicle command (TODO divide linear and ang vel??)
figure
hold on;
for i = 5:10
    a(:) = yDot(i,1,:);
    plot(seconds, a);
end
xlabel('time [s]');
leg = legend('$\dot{x}$','$\dot{y}$', '$\dot{z}$', '$w_x$', '$w_y$', '$w_z$');
ylab = ylabel('vehicle commands [m/s], [rad/s]');
tq = title(strcat(robotName, 'Vehicle command sent (yDot[5:10])'));
set(leg, 'Interpreter', 'latex', 'FontSize' , legFontSize);
set (tq, 'Interpreter', 'none', 'FontSize' , titleFontSize);
set (ylab, 'Interpreter', 'none', 'FontSize', ylabFontSize);
hold off
