
#mean calculation
n4.mean = weighted.mean(tempN_4$`SCS Length`, tempN_4$Count)
n5.mean = weighted.mean(tempN_5$`SCS Length`, tempN_5$Count)
n6.mean = weighted.mean(tempN_6$`SCS Length`, tempN_6$Count)
n7.mean = weighted.mean(tempN_7$`SCS Length`, tempN_7$Count)
n8.mean = weighted.mean(temp$`SCS Length`, temp$Count)
n9.mean = weighted.mean(tempN_9$`SCS Length`, tempN_9$Count)

#mean as function of n
X = c(4, 5, 6, 7, 8, 9)
Y = c(n4.mean, n5.mean, n6.mean, n7.mean, n8.mean, n9.mean)
p = plot(X, Y, xlab="n", ylab="Length SCS", col="blue")
reg<-lm(Y ~ X)
abline(reg,col="red")

#distance of mean from 1.5n
X = c(4, 5, 6, 7, 8, 9)
Y = c(n4.mean-6, n5.mean-7.5, n6.mean-9, n7.mean-10.5, n8.mean-12, n9.mean-13.5)
Y = abs(Y)
p = plot(X, Y, xlab="n", ylab="Length SCS", col="blue")

#variance calculation
library(Hmisc)
n4.var = wtd.var(tempN_4$`SCS Length`, tempN_4$Count)
n5.var = wtd.var(tempN_5$`SCS Length`, tempN_5$Count)
n6.var = wtd.var(tempN_6$`SCS Length`, tempN_6$Count)
n7.var = wtd.var(tempN_7$`SCS Length`, tempN_7$Count)
n8.var = wtd.var(temp$`SCS Length`, temp$Count)
n9.var = wtd.var(tempN_9$`SCS Length`, tempN_9$Count)
X1 = c(4, 5, 6, 7, 8, 9)
Y1 = c(n4.var, n5.var, n6.var, n7.var, n8.var, n9.var)
p1 = plot(X1, Y1, xlab="n", ylab="Variance SCS", col="blue")
reg1<-lm(Y1 ~ X1)
abline(reg1,col="red")

#data presention ad histogram
n = 4
x = seq(n, 2*n, length=1000)
n4.hist = plot(y=tempN_4$Count/sum(tempN_4$Count),x= tempN_4$`SCS Length`, type="h")
y = dnorm(x, mean=n4.mean, sd=sqrt(n4.var))
lines(x,y, col='blue', lwd=2)
n = 5
x = seq(n, 2*n, length=1000)
n5.hist = plot(y=tempN_5$Count/sum(tempN_5$Count),x= tempN_5$`SCS Length`, type="h")
y = dnorm(x, mean=n5.mean, sd=sqrt(n5.var))
lines(x,y, col='blue', lwd=2)
n = 6
x = seq(n, 2*n, length=1000)
n6.hist = plot(y=tempN_6$Count/sum(tempN_6$Count),x= tempN_6$`SCS Length`, type="h")
y = dnorm(x, mean=n6.mean, sd=sqrt(n6.var))
lines(x,y, col='blue', lwd=2)
n = 7
x = seq(n, 2*n, length=1000)
n7.hist = plot(y=tempN_7$Count/sum(tempN_7$Count),x= tempN_7$`SCS Length`, type="h")
y = dnorm(x, mean=n7.mean, sd=sqrt(n7.var))
lines(x,y, col='blue', lwd=2)
n = 8
x = seq(n, 2*n, length=1000)
n8hist = plot(y=temp$Count/sum(temp$Count),x= temp$`SCS Length`, type="h")
y = dnorm(x, mean=n8.mean, sd=sqrt(n8.var))
lines(x,y, col='blue', lwd=2)
n = 9
x = seq(n, 2*n, length=1000)
n9.hist = plot(y=tempN_9$Count/sum(tempN_9$Count),x= tempN_9$`SCS Length`, type="h")
y = dnorm(x, mean=n9.mean, sd=sqrt(n9.var))
lines(x,y, col='blue', lwd=2)

#qqplot
data = tempN_5
mean = n5.mean
sd = sqrt(n5.var)
x.sort = c()
for (i in 1:length(data$Count)){
  x.sort = c(x.sort, rep.int(data$`SCS Length`[i], data$Count[i]))
}
n=length(x.sort)
val=((1:n-1/2)/n)
norm.q=qnorm(val)
plot(norm.q,x.sort)
abline(mean,sd,col="blue")
