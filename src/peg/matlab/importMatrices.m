function out =  importMatrices(filename)

%# open file and read all lines
fid = fopen(filename, 'rt');
temp = textscan(fid, '%s', 'delimiter', '\n');
temp = [temp{:}];
fclose(fid);

%# find empty lines
idxSep = find(cellfun(@isempty, temp));
%# separate matrices to different cells
temp2 = mat2cell(temp, diff([0; idxSep; numel(temp)]), 1);
%# remove empty lines
temp2(1:end-1) = cellfun(@(x) x(1:end-1), temp2(1:end-1), 'UniformOutput',0);

%# convert cell arrays to double
out = cell(size(temp2));
for k = 1:numel(temp2)
    out{k} = cellfun(@str2num, temp2{k}, 'UniformOutput',0);
end
out = cellfun(@cell2mat, out, 'UniformOutput', 0);


