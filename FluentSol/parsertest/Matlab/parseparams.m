function [str, stat] = parseparams(filename)
% przetwarza plik z parametrami, jeœli jakiœ b³¹d ogólny to zwraca TRUE w
% stat. W str struktura z parametrami

str = struct('FLUENT_PATH','',	'val_FLUENT_PATH',0,...
             'DATA_PATH','',	'val_DATA_PATH',0,...
             'COMMAND_LINE','',	'val_COMMAND_LINE',0,...
             'CASE_NAME','',	'val_CASE_NAME',0,...
             'ERR','',			'val_ERR',0); % err zawsze ostatni
 
stat = 0;

fid = fopen(filename,'r');
if(fid==-1)
    stat = 1;   % true
    str.val_ERR = 1;
    str.ERR = ['Cant open config file ',filename, ' on ', cd,' Check if the file exists and have correct name'];
    return;
end
    
[message, errnum] = ferror(fid);
if(errnum~=0)
    stat = 1;   % true
    str.val_ERR = 1;
    str.ERR = message;
    return;
end

tline = 1;
linenum = 1;
while(tline~=-1)
    tline = fgets(fid);
    if(tline==-1)
        break;
    end
    if(tline(1)=='#' && tline(2)=='#')
        linenum = linenum + 1;
        continue;   % komentarz
    end
    if(tline(1)=='#')
        % tu remove_spaces
        tline = remwhitechars(tline);
        switch(tline)
            case '#FLUENT_PATH'
                command = fgets(fid);
                if(command(1)=='#')
                    stat = 1;
                    str.val_ERR = 1;
                    str.ERR = ['No data below command in line ',num2str(linenum)];
                    break;                    
                end
                command = remwhitechars(command);
                str.val_FLUENT_PATH = 1;
                str.FLUENT_PATH = command;
            case '#DATA_PATH'
                command = fgets(fid);
                if(command(1)=='#')
                    stat = 1;
                    str.val_ERR = 1;
                    str.ERR = ['No data below command in line ',num2str(linenum)];
                    break;                    
                end
                command = remwhitechars(command);
                str.val_DATA_PATH = 1;
                str.DATA_PATH = command;    
            case '#COMMAND_LINE'
                command = fgets(fid);
                if(command(1)=='#')
                    stat = 1;
                    str.val_ERR = 1;
                    str.ERR = ['No data below command in line ',num2str(linenum)];
                    break;                    
                end
                command = remwhitechars(command);
                str.val_COMMAND_LINE = 1;
                str.COMMAND_LINE = command;
            case '#CASE_NAME'
                command = fgets(fid);
                if(command(1)=='#')
                    stat = 1;
                    str.val_ERR = 1;
                    str.ERR = ['No data below command in line ',num2str(linenum)];
                    break;                    
                end
                command = remwhitechars(command);
                str.val_CASE_NAME = 1;
                str.CASE_NAME = command;
            otherwise
                stat = 1;
                str.val_ERR = 1;
                str.ERR = ['Unknown command in line ',num2str(linenum)];
                break;
        end
    end  
    linenum = linenum + 1;
end
fclose(fid);

function out = remwhitechars(in)

if(length(in)>2)
    if(in(end)==10 && in(end-1)==13)
        out = in(1:end-2);
    else
        out = in;
    end
else
    out = in;
end