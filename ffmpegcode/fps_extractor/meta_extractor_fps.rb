

dir = ARGV[0]
puts dir


path = dir + '\Pos0\metadata.txt'
fout = dir + '\fps.txt'
puts path
str = ''
i = 1
File.open(path) do |f|
  f.each_line do |line|
    if line =~ /.*ElapsedTime-ms.*/ then
        str =str + line[/\d+/] + "\n"
		puts i
		i+=1
    end
  end
end


File.open(fout, 'w') { |file| file.write(str) }
