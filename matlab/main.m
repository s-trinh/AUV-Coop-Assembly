clearvars;

rootPath = '~/LogPeg/without/';
robotNameA = 'g500_A';
robotNameB = 'g500_B';
coordName = 'Coordinator/';

%millisecond indicated in missionManager
global sControlLoop
sControlLoop = 0.1;

%% plot Task things

% taskName = 'ARM_SHAPE';
% 
% plotTask(rootPath, robotName, taskName);

%% plot yDots (command sent to robot)
% plotYDot(rootPath, robotNameA, 'yDotTPIK1');
% plotYDot(rootPath, robotNameA, 'yDotFinal');
% plotYDot(rootPath, robotNameB, 'yDotTPIK1');
% plotYDot(rootPath, robotNameB, 'yDotFinal');

%% plot coord things
% plotNonCoopVel(rootPath, coordName, robotNameA);
% plotNonCoopVel(rootPath, coordName, robotNameB);
% plotCoopVel(rootPath, coordName);
% plotCoopGeneric(rootPath, coordName, 'weightA');
% plotCoopGeneric(rootPath, coordName, 'weightB');
% plotCoopGeneric(rootPath, coordName, 'notFeasibleCoopVel');
% plotCoopGeneric(rootPath, coordName, 'idealTool');
%plotDifferenceCoopVel(rootPath, robotNameA, robotNameB)
%plotStressTool(rootPath, coordName);


%% diff tra feasabile e non coop velocities
% legFontSize = 13;
% titleFontSize = 16;
% ylabFontSize = 15;
% 
% fileName = strcat('nonCoopVel', robotNameB, '.txt');
% xDot1 = importMatrices(strcat(rootPath, coordName, fileName));
% nRow = size(xDot1, 1);
% nStep = size(xDot1, 3);
% 
% %millisecond indicated in missionManager
% totSecondPassed = sControlLoop*(nStep-1);
% seconds = 0:sControlLoop:totSecondPassed;
% 
% fileName = strcat('idealTool', '.txt');
% xDot2 = importMatrices(strcat(rootPath, coordName, fileName));
% 
% diff = xDot2 - xDot1;
% figure
% hold on;
% for i = 1:nRow
%     a(:) = diff(i,1,:);
%     plot(seconds, a);
% end
% xlabel('time [s]');


%% Vision
pathName ="~/LogPegVision/today222/g500_C/errorStereoL.txt";
plotGenericErrorDivided(pathName)