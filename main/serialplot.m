function plot_serial_input_last_20()
    % Define serial port - replace 'COM3' with your serial port
    s = serialport('/dev/ttyACM0', 115200);

    % Prepare the figure for plotting
    h = figure;
    ax = axes('Parent', h);
    grid on;
    hold(ax, 'on');
    xlabel(ax, 'X Position');
    ylabel(ax, 'Y Position');
    title(ax, 'Real-time 2D Position Tracking of Last 20 Results');

    % Initialize an empty array to store the plot
    hPlot = plot(ax, nan, nan, 'o-');

    % Loop to read and update data until the figure is closed
    while ishandle(h)
        % Read the next line of data from the serial port
        for attempt = 1:2000
            try
                % Read the next line of data from the serial port
                dataStr = readline(s);
                break; % If readline is successful, break out of the loop
            catch
                % If an error occurred while reading, try to reconnect
                clear s;
                try
                    s = serialport('/dev/ttyACM0', 115200);
                catch
                pause(1); % Wait for 1 second before the next attempt
            end
        end

        % Parse the incoming data as numbers
     try
        % Parse the incoming data as numbers
        dataNum = str2double(split(dataStr, ','));
    catch
        % If an error occurred while parsing, skip this iteration
        continue;
    end
        
        if length(dataNum) == 2 && all(~isnan(dataNum))
            % Update the plot data
            newX = dataNum(1);
            newY = dataNum(2);
            hPlot.XData = [hPlot.XData, newX]; % Append new x value
            hPlot.YData = [hPlot.YData, newY]; % Append new y value
            
            % Keep only the last 20 results
            if length(hPlot.XData) > 5
                hPlot.XData = hPlot.XData(end-4:end);
                hPlot.YData = hPlot.YData(end-4:end);
            end
            
% plot red start at -40,0 and at 40,0
            plot(ax, [-40, 40], [0, 0], 'r*');

            % Automatically adjust axes limits
            % ax.XLim = [min(hPlot.XData)-1, max(hPlot.XData)+1];
            % ax.YLim = [min(hPlot.YData)-1, max(hPlot.YData)+1];
            ax.XLim = [-100, 100];
            ax.YLim = [-100, 100];
            % Refresh the plot
            drawnow;

            % display(dataNum);
        end
    end
    
    % Clean up once the figure is closed
    clear s;
end