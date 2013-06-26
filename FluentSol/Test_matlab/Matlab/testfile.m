function out = testfile(name)

fid = fopen(name, 'w');

fprintf(fid,'Test\n');

fclose(fid)
out = 1;