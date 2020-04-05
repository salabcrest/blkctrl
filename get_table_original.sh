#!/bin/sh
dumpe2fs /dev/sdx1 | ruby get_bitmap_table_original.rb > group_table.tbl;
