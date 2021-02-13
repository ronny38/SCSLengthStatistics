#reading the data
N4.data <- read.csv("C:/Users/oref1/Technion/Sem5/SCS/temp/N=4.csv")
N5.data <- read.csv("C:/Users/oref1/Technion/Sem5/SCS/temp/N=5.csv")
N6.data <- read.csv("C:/Users/oref1/Technion/Sem5/SCS/temp/N=6.csv")
N7.data <- read.csv("C:/Users/oref1/Technion/Sem5/SCS/temp/N=7.csv")
N8.data <- read.csv("C:/Users/oref1/Technion/Sem5/SCS/temp/N=8.csv")
N9.data <- read.csv("C:/Users/oref1/Technion/Sem5/SCS/temp/N=9.csv")
N10.data <- read.csv("C:/Users/oref1/Technion/Sem5/SCS/temp/N=10.csv")
N11.data <- read.csv("C:/Users/oref1/Technion/Sem5/SCS/temp/N=11.csv")
N12.data <- read.csv("C:/Users/oref1/Technion/Sem5/SCS/temp/N=12.csv")
N13.data <- read.csv("C:/Users/oref1/Technion/Sem5/SCS/temp/N=13.csv")
N14.data <- read.csv("C:/Users/oref1/Technion/Sem5/SCS/temp/N=14.csv")
N15.data <- read.csv("C:/Users/oref1/Technion/Sem5/SCS/temp/N=15.csv")
N16.data <- read.csv("C:/Users/oref1/Technion/Sem5/SCS/temp/N=16.csv")
N17.data <- read.csv("C:/Users/oref1/Technion/Sem5/SCS/temp/N=17.csv")
N18.data <- read.csv("C:/Users/oref1/Technion/Sem5/SCS/temp/N=18.csv")
N20.data <- read.csv("C:/Users/oref1/Technion/Sem5/SCS/temp/N=20.csv")

#mean calculation
n4.mean = weighted.mean(N4.data$SCS.Length, N4.data$Count)
n5.mean = weighted.mean(N5.data$SCS.Length, N5.data$Count)
n6.mean = weighted.mean(N6.data$SCS.Length, N6.data$Count)
n7.mean = weighted.mean(N7.data$SCS.Length, N7.data$Count)
n8.mean = weighted.mean(N8.data$SCS.Length, N8.data$Count)
n9.mean = weighted.mean(N9.data$SCS.Length, N9.data$Count)
n10.mean = weighted.mean(N10.data$SCS.Length, N10.data$Count)
n11.mean = weighted.mean(N11.data$SCS.Length, N11.data$Count)
n12.mean = weighted.mean(N12.data$SCS.Length, N12.data$Count)
n13.mean = weighted.mean(N13.data$SCS.Length, N13.data$Count)
n14.mean = weighted.mean(N14.data$SCS.Length, N14.data$Count)
n15.mean = weighted.mean(as.numeric(N15.data$SCS.Length), as.numeric(N15.data$Count))
n16.mean = weighted.mean(as.numeric(N16.data$SCS.Length), as.numeric(N16.data$Count))
n17.mean = weighted.mean(N17.data$SCS.Length, N17.data$Count)
n18.mean = weighted.mean(N18.data$SCS.Length, N18.data$Count)
n20.mean = weighted.mean(N20.data$SCS.Length, N20.data$Count)

#mean as function of n
X = c(4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 20)
Y = c(n4.mean, n5.mean, n6.mean, n7.mean, n8.mean, n9.mean, n10.mean, n11.mean, n12.mean, n13.mean, n14.mean, n15.mean, n16.mean, n17.mean, n18.mean, n20.mean)
p = plot(X, Y, xlab="n", ylab="Average Length SCS", col="blue", main="Mean as function of n")
reg<-lm(Y ~ X)
abline(reg,col="red")

#distance of mean from a*n
X = c(4, 6, 8, 10, 12, 14, 16, 18)
Y = c(n4.mean-(4*(37.0/30)), n6.mean-(6*(37.0/30)), n8.mean-(8*(37.0/30)), n10.mean-(10*(37.0/30)), n12.mean-(12*(37.0/30)), n14.mean-(14*(37.0/30)), n16.mean-(16*(37.0/30)), n18.mean-(18*(37.0/30)))
Y = abs(Y)
p = plot(X, Y, xlab="n", ylab="Length SCS", col="blue")

#variance calculation
library(Hmisc)
n4.var = wtd.var(N4.data$SCS.Length, N4.data$Count)
n5.var = wtd.var(N5.data$SCS.Length, N5.data$Count)
n6.var = wtd.var(N6.data$SCS.Length, N6.data$Count)
n7.var = wtd.var(N7.data$SCS.Length, N7.data$Count)
n8.var = wtd.var(N8.data$SCS.Length, N8.data$Count)
n9.var = wtd.var(N9.data$SCS.Length, N9.data$Count)
n10.var = wtd.var(N10.data$SCS.Length, N10.data$Count)
n11.var = wtd.var(N11.data$SCS.Length, N11.data$Count)
n12.var = wtd.var(N12.data$SCS.Length, N12.data$Count)
n13.var = wtd.var(N13.data$SCS.Length, N13.data$Count)
n14.var = wtd.var(N14.data$SCS.Length, N14.data$Count)
n15.var = wtd.var(as.numeric(N15.data$SCS.Length), as.numeric(N15.data$Count))
n16.var = wtd.var(as.numeric(N16.data$SCS.Length), as.numeric(N16.data$Count))
n17.var = wtd.var(N17.data$SCS.Length, N17.data$Count)
n18.var = wtd.var(N18.data$SCS.Length, N18.data$Count)
n20.var = wtd.var(N20.data$SCS.Length, N20.data$Count)

#variance as function of n
Y = c(n4.var, n5.var, n6.var, n7.var, n8.var, n9.var, n10.var, n11.var, n12.var, n13.var, n14.var, n15.var, n16.var, n17.var, n18.var, n20.var)
p1 = plot(X, Y, xlab="n", ylab="Variance Length SCS", col="blue", main="Variance as function of n")
reg1<-lm(Y ~ X)
abline(reg1,col="red")

#data presention ad histogram
n = 4
x = seq(n, 2*n, length=1000)
n4.hist = plot(y=N4.data$Count/sum(N4.data$Count),x= N4.data$SCS.Length, type="h",xlab="Length SCS", ylab="Probability", main="Distribution function for n=4")
y = dnorm(x, mean=n4.mean, sd=sqrt(n4.var))
lines(x,y, col='blue', lwd=2)
n = 5
x = seq(n, 2*n, length=1000)
n5.hist = plot(y=N5.data$Count/sum(N5.data$Count),x= N5.data$SCS.Length, type="h",xlab="Length SCS", ylab="Probability", main="Distribution function for n=5")
y = dnorm(x, mean=n5.mean, sd=sqrt(n5.var))
lines(x,y, col='blue', lwd=2)
n = 6
x = seq(n, 2*n, length=1000)
n6.hist = plot(y=N6.data$Count/sum(N6.data$Count),x= N6.data$SCS.Length, type="h",xlab="Length SCS", ylab="Probability", main="Distribution function for n=6")
y = dnorm(x, mean=n6.mean, sd=sqrt(n6.var))
lines(x,y, col='blue', lwd=2)
n = 7
x = seq(n, 2*n, length=1000)
n7.hist = plot(y=N7.data$Count/sum(N7.data$Count),x= N7.data$SCS.Length, type="h",xlab="Length SCS", ylab="Probability", main="Distribution function for n=7")
y = dnorm(x, mean=n7.mean, sd=sqrt(n7.var))
lines(x,y, col='blue', lwd=2)
n = 8
x = seq(n, 2*n, length=1000)
n8.hist = plot(y=N8.data$Count/sum(N8.data$Count),x= N8.data$SCS.Length, type="h",xlab="Length SCS", ylab="Probability", main="Distribution function for n=8")
y = dnorm(x, mean=n8.mean, sd=sqrt(n8.var))
lines(x,y, col='blue', lwd=2)
n = 9
x = seq(n, 2*n, length=1000)
n9.hist = plot(y=N9.data$Count/sum(N9.data$Count),x= N9.data$SCS.Length, type="h",xlab="Length SCS", ylab="Probability", main="Distribution function for n=9")
y = dnorm(x, mean=n9.mean, sd=sqrt(n9.var))
lines(x,y, col='blue', lwd=2)
n = 10
x = seq(n, 2*n, length=1000)
n10.hist = plot(y=N10.data$Count/sum(N10.data$Count),x= N10.data$SCS.Length, type="h",xlab="Length SCS", ylab="Probability", main="Distribution function for n=10")
y = dnorm(x, mean=n10.mean, sd=sqrt(n10.var))
lines(x,y, col='blue', lwd=2)
n = 11
x = seq(n, 2*n, length=1000)
n11.hist = plot(y=N11.data$Count/sum(N11.data$Count),x= N11.data$SCS.Length, type="h",xlab="Length SCS", ylab="Probability", main="Distribution function for n=11")
y = dnorm(x, mean=n11.mean, sd=sqrt(n11.var))
lines(x,y, col='blue', lwd=2)
n = 12
x = seq(n, 2*n, length=1000)
n12.hist = plot(y=N12.data$Count/sum(N12.data$Count),x= N12.data$SCS.Length, type="h",xlab="Length SCS", ylab="Probability", main="Distribution function for n=12")
y = dnorm(x, mean=n12.mean, sd=sqrt(n12.var))
lines(x,y, col='blue', lwd=2)
n = 13
x = seq(n, 2*n, length=1000)
n13.hist = plot(y=N13.data$Count/sum(N13.data$Count),x= N13.data$SCS.Length, type="h",xlab="Length SCS", ylab="Probability", main="Distribution function for n=13")
y = dnorm(x, mean=n13.mean, sd=sqrt(n13.var))
lines(x,y, col='blue', lwd=2)
n = 14
x = seq(n, 2*n, length=1000)
n14.hist = plot(y=N14.data$Count/sum(N14.data$Count),x= N14.data$SCS.Length, type="h",xlab="Length SCS", ylab="Probability", main="Distribution function for n=14")
y = dnorm(x, mean=n14.mean, sd=sqrt(n14.var))
lines(x,y, col='blue', lwd=2)
n = 15
x = seq(n, 2*n, length=1000)
n15.hist = plot(y=N15.data$Count/sum(N15.data$Count),x= N15.data$SCS.Length, type="h",xlab="Length SCS", ylab="Probability", main="Distribution function for n=15")
y = dnorm(x, mean=n15.mean, sd=sqrt(n15.var))
lines(x,y, col='blue', lwd=2)
n = 16
x = seq(n, 2*n, length=1000)
n16.hist = plot(y=N16.data$Count/sum(N16.data$Count),x= N16.data$SCS.Length, type="h",xlab="Length SCS", ylab="Probability", main="Distribution function for n=16")
y = dnorm(x, mean=n16.mean, sd=sqrt(n16.var))
lines(x,y, col='blue', lwd=2)
n = 17
x = seq(n, 2*n, length=1000)
n17.hist = plot(y=N17.data$Count/sum(N17.data$Count),x= N17.data$SCS.Length, type="h",xlab="Length SCS", ylab="Probability", main="Distribution function for n=17")
y = dnorm(x, mean=n17.mean, sd=sqrt(n17.var))
lines(x,y, col='blue', lwd=2)
n = 18
x = seq(n, 2*n, length=1000)
n18.hist = plot(y=N18.data$Count/sum(N18.data$Count),x= N18.data$SCS.Length, type="h",xlab="Length SCS", ylab="Probability", main="Distribution function for n=18")
y = dnorm(x, mean=n18.mean, sd=sqrt(n18.var))
lines(x,y, col='blue', lwd=2)
n = 20
x = seq(n, 2*n, length=1000)
n20.hist = plot(y=N20.data$Count/sum(N20.data$Count),x= N20.data$SCS.Length, type="h",xlab="Length SCS", ylab="Probability", main="Distribution function for n=20")
y = dnorm(x, mean=n20.mean, sd=sqrt(n20.var))
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
