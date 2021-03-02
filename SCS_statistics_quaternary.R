# Statistics about the SCS data for the quaternary case.

# Global parameters
min_n = 3 # Minimum length of strands
max_n = 9 # Maximum length of strands
git_dir = "C:/Users/IsrealIsreali/Coding" #path of the git project directory

# Change the directory
dir = paste0(git_dir, "/SCSLengthStatistics/data_DNA")
setwd(dir)

# Creating vectors for the data
length_vec = seq(1, min_n-1, by=1)
count_vec = seq(1, min_n-1, by=1)
data_vec = seq(1, min_n-1, by=1)

# Reading the data from the csv files
for (i in min_n:max_n){
  file_name = paste0("./tempN=", i, ".csv")
  data_arg <- read.csv(file_name)
  length_vec <- append(length_vec, data_arg[1])
  count_vec <- append(count_vec ,data_arg[2])
}

# mean calculation
mean_vec = seq(1, max_n, by=1)
for (i in min_n:max_n){
  mean_vec[i] <- weighted.mean(as.numeric(length_vec[i]$SCS.Length), as.numeric(count_vec[i]$Count))
}

#' Representing mean as a function of strand length
#' 
#' @example
#' Mean_Plot()
Mean_Plot <- function(){
  x = seq(min_n, max_n, by=1)
  y = mean_vec[min_n:max_n]
  reg<-lm(y ~ x)
  coef=coef(reg)
  main = paste0("Mean as a function of strand length\n", "y=", round(coef[2], 3), "x+", round(coef[1],3))
  plot(x=x, y=y, xlab="Strand length", ylab="Average Length SCS", col="blue", main=main, ylim=c(min_n,1.7*max_n))
  text(x=x, y=y+0.5, labels=round(y, 3))
  abline(reg,col="red")
}

# Variance calculation
library(Hmisc)
var_vec = seq(1, max_n, by=1)
for (i in min_n:max_n){
  var_vec[i] <- wtd.var(as.numeric(length_vec[i]$SCS.Length), as.numeric(count_vec[i]$Count))
}


#' Representing variance as a function of strand length
#' 
#' @example
#' Var_Plot()
Var_Plot <- function(){
  x = seq(min_n, max_n, by=1)
  y = var_vec[min_n:max_n]
  reg<-lm(y ~ x)
  coef=coef(reg)
  main = paste0("Variance as a function of strand length\n", "y=", round(coef[2], 3), "x+", round(coef[1],3))
  plot(x=x, y=y, xlab="Strand length", ylab="Variance Length SCS", col="blue", main=main, ylim=c(0,1))
  text(x=x, y=y+0.1, labels=round(y, 3))
  abline(reg,col="red")
}


#' Representing distribution for specified strand length
#' 
#' @param N n number - strand length
#' @param add_norm_func show or not show normal function according to mean and var.
#' @examples
#' dist_for_n(7)
#' dist_for_n(8, TRUE)
dist_for_n <- function(N, add_norm_func = FALSE){
  stopifnot (N<=max_n)
  main = paste0("A distribution function for strand length of ", N)
  y = count_vec[N]$Count/sum(count_vec[N]$Count)
  x = length_vec[N]$SCS.Length
  plot(y=y,x=x, type="h", xlab="Length SCS", ylab="Probability", main=main, lwd=3, ylim=c(0,1), xaxp = c(N, 2*N, N))
  text(x=x, y=y+0.1, labels=round(y, 3))
  if (add_norm_func == TRUE){ 
    x = seq(N, 2*N, length=1000)
    y = dnorm(x, mean=mean_vec[N], sd=sqrt(var_vec[N]))
    lines(x,y, col='blue', lwd=2)
    normal_text = paste0("Normal distiribution function\n","Mean = ", round(mean_vec[N], 3),", Var = ", round(var_vec[N], 3)) 
    legend(x[1],1,c("Collected data",normal_text), lwd=c(3,2), col=c("black","blue"),  y.intersp = 0.5)
  }
}