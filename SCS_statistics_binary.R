# Statistics about the SCS data.

# Global parameters
min_n = 4 # Minimum length of strands
max_n = 29 # Maximum length of strands

#' Change the directory
#' 
#' @param git_dir directory of the git project directory
#' @examples
#' change_dir("C:/Users/IsrealIsreali/Coding")
change_dir <- function(git_dir){
  dir = paste0(git_dir, "/SCSLengthStatistics/data_binary")
  setwd(dir)
}

# Creating vectors for the data
length_vec = seq(1, min_n-1, by=1)
count_vec = seq(1, min_n-1, by=1)
data_vec = seq(1, min_n-1, by=1)

# Reading the data form the csv files
# Full data until 20, randomized data from 21
for (i in min_n:max_n){
  file_name = paste0("./N=", i, ".csv")
  data_arg <- read.csv(file_name)
  length_vec <- append(length_vec, data_arg[1])
  count_vec <- append(count_vec ,data_arg[2])
}

# mean calculation
mean_vec = seq(1, max_n, by=1)
for (i in min_n:max_n){
  mean_vec[i] <- weighted.mean(as.numeric(length_vec[i]$SCS.Length), as.numeric(count_vec[i]$Count))
}

# Representing mean as function of strand length
X = seq(min_n, max_n, by=1)
reg<-lm(mean_vec[min_n:max_n] ~ X)
coef=coef(reg)
main = paste0("Mean as function of strand length\n", "y=", round(coef[2], 3), "x+", round(coef[1],3))
plot(X, mean_vec[min_n:max_n], xlab="Strand length", ylab="Average Length SCS", col="blue", main=main)
abline(reg,col="red")

# Variance calculation
library(Hmisc)
var_vec = seq(1, max_n, by=1)
for (i in min_n:max_n){
  var_vec[i] <- wtd.var(as.numeric(length_vec[i]$SCS.Length), as.numeric(count_vec[i]$Count))
}

# Representing variance as function of strand length
reg<-lm(var_vec[min_n:max_n] ~ X)
coef=coef(reg)
main = paste0("Var as function of strand length\n", "y=", round(coef[2], 3), "x+", round(coef[1],3))
plot(X, var_vec[min_n:max_n], xlab="Strand length", ylab="Variance Length SCS", col="blue", main=main)
abline(reg,col="red")


#' Represting histogram for specified strand length
#' 
#' @param N n number - strand length
#' @param add_norm_func showing norm function accroding to mean and var
#' @examples
#' data_rep_and_hist(27)
#' data_rep_and_hist(25, TRUE)
data_rep_and_hist <- function(N, add_norm_func = FALSE){
  stopifnot (N<=max_n)
  x = seq(N, 2*N, length=1000)
  main = paste0("Distribution function for strand length=", N)
  plot(y=count_vec[N]$Count/sum(count_vec[N]$Count),x= length_vec[N]$SCS.Length, type="h",xlab="Length SCS", ylab="Probability", main=main)
  y = dnorm(x, mean=mean_vec[N], sd=sqrt(var_vec[N]))
  if (add_norm_func == TRUE){ lines(x,y, col='blue', lwd=2)}
}