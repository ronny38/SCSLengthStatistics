
Y=rbind(temp0, temp1, temp2, temp3, temp4, temp5, temp6, temp7)
X = Y$`SCS Length`
mean(X)
sd(X)
h = hist(X, breaks=seq(4,8,1), xlab="Length SCS", col="blue")