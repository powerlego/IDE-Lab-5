% Real time data collection example
%
% This script is implemented as a function so that it can
%   include sub-functions
%
% This script can be modified to be used on any platform by changing the
% serialPort variable.
% Example:-
% On Linux:     serialPort = '/dev/ttyS0';
% On MacOS:     serialPort = '/dev/tty.KeySerial1';
% On Windows:   serialPort = 'COM1';
%
%To run: 
%plot_cams()
%To reset ports: (if MATLAB still thinks they're busy)
%delete(instrfindall)
%

function plot_cameras_serial_blank ()

%Send over bluetooth or serial
serialPort = 'COM3';
serialObject = serial(serialPort);
%configure serial connection
serialObject.BaudRate = 115200; %(Default)
%serialObject.BaudRate = 115200;
%serialObject.FlowControl = 'software';

%Initiate serial connection
fopen(serialObject);

% This gets called on cleanup to ensure the stream gets closed
finishup = onCleanup(@() myCleanupFun(serialObject));

% Instantiate variables
count = 1;
trace = zeros(1, 128); %Stored Values for Raw Input


while (1)
    % Check for data in the stream
    if serialObject.BytesAvailable
        val = fscanf(serialObject,'%f');
        check = (val == -1) || (val == -3);
        if (check) % -1 and -3 are start keywords
            count = 1;
            %val
        elseif (val == -2) % End camera1 tx
            if (count >= 128)
                plotdata(trace, 1);
            end %otherwise there was an error and don't plot
            count = 1;
            %plotdata(trace);
        elseif (val == -4) % End camera2 tx
            count = 1;
            plotdata(trace, 2);
        else
            trace(count) = val;
            count = count + 1;
        end % if 
        
    end %bytes available 
end % while(1)

% Clean up the serial object
fclose(serialObject);
delete(serialObject);
clear serialObject;

end %plot_cams

%*****************************************************************************************************************
%*****************************************************************************************************************

function plotdata(trace, cam)
drawnow;
subplot(4,2,cam);
%figure(figureHandle);
plot(trace);
%set(figureHandle,'Visible','on');
bintrace = zeros(1,128); %Stored Values for Edge Detection
smoothtrace = zeros(1,128);
%SMOOTH AND PLOT
%smoothtrace = movmean(trace,5,'Endpoints',trace(128));
% for i = 1:128
%      if(i > (128-5))
%          if (128-i==4)
%              smoothtrace(i) = (trace(i)+trace(i+1)+trace(i+2)+trace(i+3)+trace(128))/5;
%          elseif (128-i == 3)
%              smoothtrace(i) = (trace(i)+trace(i+1)+trace(i+2)+2*trace(128))/5;
%          elseif (128-i == 2)
%              smoothtrace(i) = (trace(i)+trace(i+1)+3*trace(128))/5;
%          elseif (128-i == 1)
%              smoothtrace(i) = (trace(i)+4*trace(128))/5;
%          elseif (128-i == 0)
%              smoothtrace(i) = 5*trace(128)/5;
%          end
%      else
%          smoothtrace(i) = (trace(i)+trace(i+1)+trace(i+2)+trace(i+3)+trace(i+4))/5;
%      end
%      %5-point Averager
%      %INSERT CODE
% end
subplot(4,2,cam+2);
%figure(smoothhand);
plot(smoothtrace);

%THRESHOLD
%calculate 1's and 0's via thresholding
% maxval = max(trace);
% for i = 1:128
%     if(trace(i) == xval)
%        bintrace(i) = 1;
%     end
%     %Edge detection (binary 0 or 1)
%     %INSERT CODE
% end
% drawnow;
% subplot(4,2,cam+4);
% %figure(binfighand);
% plot(bintrace);

end %function

function myCleanupFun(serialObject)
% Clean up the serial object
fclose(serialObject);
delete(serialObject);
clear serialObject;
delete(instrfindall);
end