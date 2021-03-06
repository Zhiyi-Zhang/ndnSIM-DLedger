#!/usr/bin/env Rscript

# install.packages('ggplot2')
library(ggplot2)
# install.packages('scales')
library(scales)
# install.packages('doBy')
library(doBy)

#########################
# Rate trace processing #
#########################
args = commandArgs(trailingOnly=TRUE)
target="10nodes-5-8"

data = read.table(paste(target, "txt", sep="."), header=T)

# graph rates on selected nodes in number of incoming interest packets
g.nodes <- ggplot(NULL) +
  geom_line(data=data, aes (x=simulation.time, y=total, colour="darkblue"), size=2, linetype = "dotted") +
  geom_line(data=data, aes (x=simulation.time, y=unconfirmed, colour="red"), size=2, linetype = "solid") +
  scale_color_discrete(name = "Record Types", labels = c("total", "unconfirmed")) +
  xlab("Time [second]") +
  ylab("Records Number") +
  theme_linedraw() +
  theme(
    #legend.position="none", text = element_text(size=12),
    legend.position="top",
    legend.title = element_text(size = 25, face = "bold"),
    legend.text = element_text(size = 25, face = "bold"),
    axis.text.x = element_text(color = "grey20", size = 25, angle = 0, face = "plain"),
    axis.text.y = element_text(color = "grey20", size = 25, angle = 90, face = "plain"),
    axis.title.x = element_text(color="black", size=25, face="plain"),
    axis.title.y = element_text(color="black", size=25, face="plain")
  )

png(paste(target, "png", sep="."), width=700, height=500)
print(g.nodes)
retval <- dev.off()
g.nodes
