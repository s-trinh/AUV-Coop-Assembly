% % eul = [1.9862796881660256e-17, -4.6073563061378386e-08, -1.5707991565684896];
% 
% format long
% rotm = eul2rotm(eul,'XYZ')

% xyz = rotm2eul([  -0.01952783646  0.9997663318  -0.009270679234;
% -0.005426883134  0.009166319827  0.9999432622;
% 0.9997945852  0.01957703939  0.005246616649
% ], 'XYZ')
% 
%  eul = [-pi/2, 0, pi/2];
% rotm = eul2rotm(eul,'XYZ')
% 
% rot = [0.0001160253356  0.9999863849  -0.005216948888;
% 0.01991342897  0.005213604013  0.9997881144;
% 0.9998017013  -0.0002198880926  -0.01991255294];
%   
% eul45 = [-1.571, -1.525, -0.000]
% mat45 = eul2rotm(eul45, 'XYZ');
% 
% (        mat45* rot'             )
% eul2rotm([-pi/2, 0, pi/2], 'XYZ')


rot = [0.03244278176  0.9994333994  -0.008963598619;
-0.04404923626  0.01038938035  0.9989753378;
0.998502444  -0.03201469919  0.04436133833;
 ];

rotm2eul(rot, 'XYZ')





