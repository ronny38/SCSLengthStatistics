
#mean calculation
n4.mean = weighted.mean(N_4$`SCS Length`, N_4$Count)
n6.mean = weighted.mean(N_6$`SCS Length`, N_6$Count)
n8.mean = weighted.mean(N_8$`SCS Length`, N_8$Count)
n10.mean = weighted.mean(N_10$`SCS Length`, N_10$Count)
n12.mean = weighted.mean(N_12$`SCS Length`, N_12$Count)

#mean as function of n
X = c(4, 6, 8, 10, 12)
Y = c(n4.mean, n6.mean, n8.mean, n10.mean, n12.mean)
p = plot(X, Y, xlab="n", ylab="Length SCS", col="blue")
reg<-lm(Y ~ X)
abline(reg,col="red")

#distance of mean from 1.5n
X = c(4, 6, 8, 10, 12)
Y = c(n4.mean-(4*(4/3)), n6.mean-(6*(4/3)), n8.mean-(8*(4/3)), n10.mean-(10*(4/3)), n12.mean-(12*(4/3)))
Y = abs(Y)
p = plot(X, Y, xlab="n", ylab="Length SCS", col="blue")

#variance calculation
library(Hmisc)
n4.var = wtd.var(N_4$`SCS Length`, N_4$Count)
n6.var = wtd.var(N_6$`SCS Length`, N_6$Count)
n8.var = wtd.var(N_8$`SCS Length`, N_8$Count)
n10.var = wtd.var(N_10$`SCS Length`, N_10$Count)
n12.var = wtd.var(N_12$`SCS Length`, N_12$Count)
X1 = c(4, 6, 8, 10, 12)
Y1 = c(n4.var, n6.var, n8.var, n10.var, n12.var)
p1 = plot(X1, Y1, xlab="n", ylab="Variance SCS", col="blue")
reg1<-lm(Y1 ~ X1)
abline(reg1,col="red")

#data presention ad histogram
n = 4
x = seq(n, 2*n, length=1000)
n4.hist = plot(y=N_4$Count/sum(N_4$Count),x= N_4$`SCS Length`, type="h")
y = dnorm(x, mean=n4.mean, sd=sqrt(n4.var))
lines(x,y, col='blue', lwd=2)
n = 6
x = seq(n, 2*n, length=1000)
n6.hist = plot(y=N_6$Count/sum(N_6$Count),x= N_6$`SCS Length`, type="h")
y = dnorm(x, mean=n6.mean, sd=sqrt(n6.var))
lines(x,y, col='blue', lwd=2)
n = 8
x = seq(n, 2*n, length=1000)
n8.hist = plot(y=N_8$Count/sum(N_8$Count),x= N_8$`SCS Length`, type="h")
y = dnorm(x, mean=n8.mean, sd=sqrt(n8.var))
lines(x,y, col='blue', lwd=2)
n = 10
x = seq(n, 2*n, length=1000)
n10.hist = plot(y=N_10$Count/sum(N_10$Count),x= N_10$`SCS Length`, type="h")
y = dnorm(x, mean=n10.mean, sd=sqrt(n10.var))
lines(x,y, col='blue', lwd=2)
n = 12
x = seq(n, 2*n, length=1000)
n12.hist = plot(y=N_12$Count/sum(N_12$Count),x= N_12$`SCS Length`, type="h")
y = dnorm(x, mean=n12.mean, sd=sqrt(n12.var))
lines(x,y, col='blue', lwd=2)

#qqplot
data = tempN_8
mean = n8.mean
sd = sqrt(n8.var)
x.sort = c()
for (i in 1:length(data$Count)){
  x.sort = c(x.sort, rep.int(data$`SCS Length`[i], data$Count[i]))
}
n=length(x.sort)
val=((1:n-1/2)/n)
norm.q=qnorm(val)
plot(norm.q,x.sort)
abline(mean,sd,col="blue")
