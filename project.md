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

## Presentation (due 6/7)

**The presentation will be 30% of your project grade**

We will have the class conference from 11:30am-2pm in Kemper 3083.

All group members should deliver part of the talk.
Each group will have a 15 minute slot to deliver their talk and take questions.
This will give you 12 minutes for the talk + 3 minutes for questions.
The talk should give highlights of the final report, including the problem, motivation, results, conclusions, and possible future work. Time limits will be enforced to let everyone present.
Please, practice your talk to make it better and see how long it is.
Have a plan for what slides to skip if you get behind.

[This rubric](rubric.pdf) will be used to grade your oral presentations.

## Final report due (6/13)

**The final report will be 40% of your project grade**

The format of this report is the same as the research papers you have read in class.
There are no specific page requirements.
I expect most projects will be in the 4-6 page range when using the provided template.

Use the [ACM template](https://www.acm.org/publications/proceedings-template) for your paper. 
Please use the sigconf version (e.g., `\documentclass[sigconf]{acmart}` if you're using LaTeX).

Your paper will be graded both on presentation (e.g., logical flow and data presentation) as well as whether you made progress towards the goals laid out in your proposal and mid project report.

Below is a solid starting point for an outline of a good paper. 
Most people in the class are "answering questions". 
However, I also included the outline for a more engineering-based paper (like many of the ones we read in class).

- The introduction should put your work in context of today's technology. What is the problem you're solving or question you're asking? Why does it matter? What is the solution you're proposing or the answer to the question?
- You should have a complete covering of the most relevant related work (not necessarily all of the related work, but the most closely related should be covered in detail.
- Explain the methodology you used to answer the question or explain the solution to the problem you're solving in detail. Someone reading the paper should be able to recreate (reproduce) your work.
- Show data which shows the efficacy of your solution, or gives the answer to your question. This should be detailed, likely graph-based, and you should have clear descriptions of the data.
- Finally, you should discuss/conclude the paper by recapping the main points.

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

### Comparison of different SIMD extensions

Each ISA has its own set of SIMD extensions.
x86 has [MMX, SSE, SSE2, SSSE3, AVX, AVX2, AVX512, and others](https://en.wikipedia.org/wiki/Streaming_SIMD_Extensions),
ARMv8 has "scalable" vector extentions ([SVE](https://community.arm.com/developer/tools-software/hpc/b/hpc-blog/posts/technology-update-the-scalable-vector-extension-sve-for-the-armv8-a-architecture)),
and RISC-V has its own [proposal](https://riscv.github.io/documents/riscv-v-spec/riscv-v-spec.pdf).

In this project, you could compare and contrast the programmability and performance of these extensions.
Another option would be to use an architectural simulator (e.g., gem5) to implement all of these extensions in a single CPU design and compare their performance.
gem5 currently has support for ARM's SVE, but not all of the x86 extensions or the RISC-V proposal.
(Note: updating gem5 with support for x86 and RISC-V vector instructions would be very impactful to the broader gem5 community.)

### On-chip network simulation

[Multi-chip modules](https://en.wikipedia.org/wiki/Multi-chip_module) (MCMs) are becoming common in today's packages.
Both NVIDIA GPUs and AMD server systems are build with MCMs.

While there is a plethora of research on the design of on-chip networks (OCNs) and inter-system networks (e.g., ethernet), there has not been much work on MCM networks.
This project could look at the tradeoffs between bisection bandwidth, latency, and cost for these emerging networks.

The [Synthesis Lecture on On-Chip Networks](https://www.morganclaypool.com/doi/abs/10.2200/S00772ED1V01Y201704CAC040) would be a good place to start to get some good background.
