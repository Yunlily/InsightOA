Problem
This is the OA solution for code challenge from insight bootcamp.
code challenge: https://github.com/InsightDataScience/h1b_statistics
insight data engineer bootcamp: https://www.insightconsensus.com/

Language
My implementation is written by C++.
And the shell script run.sh is implemented to run the command-line arguments.

Implementation
According to the problem described, the task is to create a mechanism to analyze past years data, specifically calculate two metrics: top 10 occuptions and Top 10 States for certified visa application.

After some observation, the data has following features:
1.Column names contains information but only three of them is needed. 
2.The data we need is under the same(almost same) index according to the column name.
3.Each line is split by '\n' and each information bar is split by ';'.

Procedure:
1.Open the "h1b_statistic.csv" first and read the first line containing column names, open two txt file named "top_10_occupations.txt" and "top_10_states.txt" to save data later.
2.Extract needed column names(certification, occupation name and worksite state) and save their indexes. index means how many ';' is ahead of this column name. 
3.Start reading each line from index 0, when its reading the certification index, check if the line is certified, if not, omit the whole line and start reading from the next line. if yes, keep reading until we get its occupation name and worksite state then save. Also, if the line is certified, add one to the counter,the counter is to save the total number of certified lines.
4.Use two maps to save the useful information we got, the key of first map should be a string to save occupation name, and the value is the number of occupation. The key of second map should be a string to save worksite state and the value of it is its number.
5.Sort the map by number in descending order and save the first 10 items from each map, also, we should add the third column which shows the percentage of each item over all certified items. Then output them to the two txt file we created just now and save them.

Analyze
The total complexity of reading information from h1b_statistics.csv is O(n).
the complexity of sorting two maps takes O(10log10).

Possible bugs:
1.Due to manual occupation fault, some data doesn't show under the specific index of its column name, would somehow affect the accuracy.
2.the column name varies, I mean, sometimes people save the worksite state as "WORKSITE_STATE", and some save it as "WORKLOC1_STATE". If the name changed in the future file, the code should be modified.

To run the code
1 git clone https://github.com/Yunlily/InsightOA.git 
2 cd InsightOA/
3 run ./run.sh  
4 cd output/
5 read top_10_occupations.txt and top_10_states.txt respectively.
