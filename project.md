---
title: ECS 201C Project
author: Jason Lowe-Power
---

# ECS 201C Project Details

A major component of your grade (40%) is a research-based project.
This project can range from describing and evaluating a new research idea like in the readings for the class to writing a review of current literature to implementing and evaluating an idea from current literature.
The main constraint on this project is it must be related to parallel/specialized architectures and it cannot be directly part of your current research.

The key is insuring that some aspects of your work are completely done.
It is very hard to grade a project where there is no results.
Be sure to include many stepwise goals.

## Project teams

All projects must be completed in precisely **teams of two**.
Preferably, at least one of the people in each team will have taken 201A or equivalent.

You may use teams and other online forums to create your teams based on your interests.
I suggest announcing your background and the kinds of projects you are interested in or any specific ideas you would like to work on.
If you are looking for a partner, you can then reach out to them.

## Proposals (due 5/7)

**The proposal will be 15% of your project grade**

[Sign up for a 15 minute meeting during our class time on 5/7](https://calendar.google.com/calendar/selfsched?sstoken=UU4yT1lsZUw4aElqfGRlZmF1bHR8YjIyNWNiNmQyZmE4MDY2MWU2OWNjOWE0NTE2MTdiZWI).
Add the name of you and your partner to the description of the event.

Your proposal should be one to two pages describing the problem you are going to address.
It should answer the following questions:

- 1-2 paragraphs on the problem. Answer the following questions:
  - What is the problem?
  - Why is this problem important? Why do *you* want to address this problem? Or why is this problem interesting?
- 1-2 paragraphs on related work
  - At this point, the related work does not have to be complete, but you should have an idea of what has been done.
  - You should cite at least 2-3 related papers.
  - Answer the question: What are you building off of?
- 1 paragraph on your ideas
  - What are your ideas to attack the problem?
- 1-2 paragraphs on your plan. Answer the following questions:
  - How will you evaluate your solution to the problem?
  - What are the concrete steps you will follow to accomplish your goals?
  - A [Gantt chart](https://en.wikipedia.org/wiki/Gantt_chart) may be useful here.
  - **Important**: Include both short term and longer term goals. Answer the question: If we cannot accomplish all of our goals, what is an intermediate goal which can be evaluated.

## Mid project report (due 5/28)

**The mid project report will be 15% of your project grade**

Progress reports should include a revised version of the proposal plus one page describing accomplishments so far.
Concentrate on describing sub-tasks completed, rather than the tasks started.
There will be meetings during class time for this report like the proposal.

## Presentation (TBD)

**The presentation will be 30% of your project grade**

We will divide up the last few lectures into 15 minute conference-style talks with 5 minutes for questions.
Depending on class size, some talk may be scheduled at alternative times.
All group members should deliver part of the talk.
The talk should give highlights of the final report, including the problem, motivation, results, conclusions, and possible future work. Time limits will be enforced to let everyone present.
Please, practice your talk to make it better and see how long it is.
Have a plan for what slides to skip if you get behind.

More info soon.

## Final report due (6/13)

**The final report will be 40% of your project grade**

The format of this report is the same as the research papers you have read in class.
There are no specific page requirements.

More info soon.

# Project ideas

Below are a set of project ideas.
However, please suggest your own as well!

The project should somehow relate to parallel and/or specialized architecture.
Some broad ideas include:

- Modifying an application or algorithm to work better on a parallel or specialized architecture.
- Modifying a parallel architecture to execute an algorithm or application more efficiently.
- Evaluating the performance of an important application on a parallel or specialized architectures.
- Exploring the design space for a specific kind of architecture (e.g., different ML accelerators)
- Exploring the design space for a specific kind of algorithm (e.g., different implementations of stochastic gradient descent)

Projects will typically have an evaluation component where code is run on some hardware and performance (or efficiency) is reported (like your assignments).
You may want to use hardware simulation platforms (e.g., [gem5](http://gem5.org/) or [GPGPU-Sim](http://www.gpgpu-sim.org/)) if you are interested in proposing *new hardware*.

## Specific project ideas

### Hybrid coherence protocol

How can you optimize the coherence protocol of a system if you have hints from software?
If you were to do a hardware-software co-design of the coherence protocol, how would you do it?

#### Related work

There is a set of work called "DeNovo" from UIUC.
The [webpage](http://rsim.cs.illinois.edu/denovo/pubs.html) has a number of publications including some GPU-specific protocols.
The [first paper on DeNovo](http://rsim.cs.illinois.edu/denovo/Pubs/11-pact-denovo.pdf) at PACT gives a good overview.

DeNovo leverages deterministic parallel Java (DPJ) to overcome some complexity.
I wonder if these ideas would be applicable to other programming models.

Looking at one specific domain (e.g., machine learning) could be a way to limit the scope of this project.


