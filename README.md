# SS2LM

An self implement the paper

《[An optimal sphere and two large margins approach for novelty detection](http://xueshu.baidu.com/usercenter/paper/show?paperid=fe73aacccbfddb64fe56f23981ff241e&site=xueshu_se)》


This paper introduced a classifier based on support vector for classification. The result in the paper shows that it could get better performance in novelty detective and we could also verify correctness from theory. However, action speaks louder than words. We need to verify it from action. I try to contact with the author [Trung.le](trung.le@canberra.edu.au) with email in 18/11/2016 but rejected. Therefore, I try my best to implement it with libsvm tool using C program language.

Below is my shabby blog with some basic introduce of SS2LM.

[My Blog](https://blog.csdn.net/u013379032/article/details/80478420#comments) 

The Folder in the Project is about the source code and a simple tool for non-technical personnel use. 

The Support vector classification can be divided by two part: training and predicting. (Most of the time are Supervised Model)

> Folder ss2lm 

-  the source project code of training machine

> Folder predict

- the source project code of classification

> SVM Ensemble toolbox

- a basic toolbox for series of SVM classification. (Include LibSVM box and ss2lm)

- <font color='red'> This toolbox with the Software copyright (No.01944766) could not be used by business use.</font>

