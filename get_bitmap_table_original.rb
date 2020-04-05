#!/usr/bin/ruby

while line = gets do
	str = (line.to_s).split
	
	if str[0] == "Group" then
		tmp = str[1].split(":")
		grpno = tmp[0].to_i
		next
	end
	
	if str[0] == "Block" && str[1] == "bitmap" then
		blkno = str[3].to_i
		print grpno, " ", blkno, "\n"
		next
	end
end

