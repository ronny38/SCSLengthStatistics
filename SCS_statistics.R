n = 9
#reading the data
#full data
setwd("C:/Users/oref1/Technion/Sem5/SCS/SCSLengthStatistics/data_DNA")
data_vec_length = c(0,0)
data_vec_count = c(0,0)
N3.data <- read.csv("./tempN=3.csv")
data_vec_length <- append(data_vec_length, N3.data[1])
data_vec_count <- append(data_vec_count, N3.data[2])
N4.data <- read.csv("./tempN=4.csv")
data_vec_length <- append(data_vec_length, N4.data[1])
data_vec_count <- append(data_vec_count, N4.data[2])
N5.data <- read.csv("./tempN=5.csv")
data_vec_length <- append(data_vec_length, N5.data[1])
data_vec_count <- append(data_vec_count, N5.data[2])
N6.data <- read.csv("./tempN=6.csv")
data_vec_length <- append(data_vec_length, N6.data[1])
data_vec_count <- append(data_vec_count, N6.data[2])
N7.data <- read.csv("./tempN=7.csv")
data_vec_length <- append(data_vec_length, N7.data[1])
data_vec_count <- append(data_vec_count, N7.data[2])
N8.data <- read.csv("./tempN=8.csv")
data_vec_length <- append(data_vec_length, N8.data[1])
data_vec_count <- append(data_vec_count, N8.data[2])
N9.data <- read.csv("./tempN=9.csv")
data_vec_length <- append(data_vec_length, N9.data[1])
data_vec_count <- append(data_vec_count, N9.data[2])

#mean calculation
mean_vec = c()
for (i in 3:n){
  mean_vec <- append(mean_vec, weighted.mean(as.numeric(data_vec_length[i]$SCS.Length), as.numeric(data_vec_count[i]$Count)))
}

#mean as function of n
X = seq(3, n, by=1)
reg<-lm(mean_vec ~ X)
coef=coef(reg)
main = paste0("Mean as function of n\n", "y=", round(coef[2], 3), "x+", round(coef[1],3))
plot(X, mean_vec, xlab="n", ylab="Average Length SCS", col="blue", main=main)
abline(reg,col="red")

#variance calculation
library(Hmisc)
var_vec = c()
for (i in 3:n){
  var_vec <- append(var_vec, wtd.var(as.numeric(data_vec_length[i]$SCS.Length), as.numeric(data_vec_count[i]$Count)))
}

#variance as function of n
reg<-lm(var_vec ~ X)
coef=coef(reg)
main = paste0("Var as function of n\n", "y=", round(coef[2], 3), "x+", round(coef[1],3))
plot(X, var_vec, xlab="n", ylab="Variance Length SCS", col="blue", main=main)
abline(reg,col="red")

#data presention ad histogram
n = 3
x = seq(n, 2*n, length=1000)
n3.hist = plot(y=N3.data$Count/sum(N3.data$Count),x= N3.data$SCS.Length, type="h", xlab="Length SCS", ylab="Probability", main="Distribution function for n=3")
y = dnorm(x, mean=mean_vec[n-2], sd=sqrt(var_vec[n-2]))
lines(x,y, col='blue', lwd=2)
n = 4
x = seq(n, 2*n, length=1000)
n4.hist = plot(y=N4.data$Count/sum(N4.data$Count),x= N4.data$SCS.Length, type="h", xlab="Length SCS", ylab="Probability", main="Distribution function for n=4")
y = dnorm(x, mean=mean_vec[n-2], sd=sqrt(var_vec[n-2]))
lines(x,y, col='blue', lwd=2)
n = 5
x = seq(n, 2*n, length=1000)
n5.hist = plot(y=N5.data$Count/sum(N5.data$Count),x= N5.data$SCS.Length, type="h", xlab="Length SCS", ylab="Probability", main="Distribution function for n=5")
y = dnorm(x, mean=mean_vec[n-2], sd=sqrt(var_vec[n-2]))
lines(x,y, col='blue', lwd=2)
n = 6
x = seq(n, 2*n, length=1000)
n6.hist = plot(y=N6.data$Count/sum(N6.data$Count),x= N6.data$SCS.Length, type="h", xlab="Length SCS", ylab="Probability", main="Distribution function for n=6")
y = dnorm(x, mean=mean_vec[n-2], sd=sqrt(var_vec[n-2]))
lines(x,y, col='blue', lwd=2)
n = 7
x = seq(n, 2*n, length=1000)
n7.hist = plot(y=N7.data$Count/sum(N7.data$Count),x= N7.data$SCS.Length, type="h", xlab="Length SCS", ylab="Probability", main="Distribution function for n=7")
y = dnorm(x, mean=mean_vec[n-2], sd=sqrt(var_vec[n-2]))
lines(x,y, col='blue', lwd=2)
n = 8
x = seq(n, 2*n, length=1000)
n8.hist = plot(y=N8.data$Count/sum(N8.data$Count),x= N8.data$SCS.Length, type="h", xlab="Length SCS", ylab="Probability", main="Distribution function for n=8")
y = dnorm(x, mean=mean_vec[n-2], sd=sqrt(var_vec[n-2]))
lines(x,y, col='blue', lwd=2)
n = 9
x = seq(n, 2*n, length=1000)
n9.hist = plot(y=N9.data$Count/sum(N9.data$Count),x= N9.data$SCS.Length, type="h", xlab="Length SCS", ylab="Probability", main="Distribution function for n=9")
y = dnorm(x, mean=mean_vec[n-2], sd=sqrt(var_vec[n-2]))
lines(x,y, col='blue', lwd=2)
