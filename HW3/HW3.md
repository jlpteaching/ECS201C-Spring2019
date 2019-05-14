# Homework 3: Map reduce

## DUE 5/16 at 10:30am (before class).
**No late assignments will be accepted!**

## Analyzing the Internet

There is an open data project which crawls the Internet, [Common Crawl](http://commoncrawl.org/).
The data is freely available on amazon s3 (which is quite convenient).

You will be performing some map reduce computations on a subset of this data.

To test locally, I suggest downloading one file from the set of all of the files.
The Common Crawl website has [a page](http://commoncrawl.org/the-data/get-started/) which describes the format of its data.
You will likely just want to use the WET format, which contains the plain-text only data.

[https://commoncrawl.s3.amazonaws.com/crawl-data/CC-MAIN-2019-18/wet.paths.gz](https://commoncrawl.s3.amazonaws.com/crawl-data/CC-MAIN-2019-18/wet.paths.gz) is a gzipped version which lists all of the 56,000 WET files of the latest crawl.
Note that uncompressed these files are almost 7 *tera*bytes.

**You should not try to run any map-reduce workload on the entire dataset!**

Locally, I suggest you download just one or two of the 56,000 files.
Each of these files is ~100 MB compressed and ~350 MB uncompressed.
You can use these files (or a subset `head -n100000 <file> > smaller-file`) to test your map-reduce locally.

I have downloaded eight of these files to Amarillo for testing.
You can find them in `/data1/ECS201C/common-crawl/`.
I split these files into ~3MB chunks, and I created an input file `/data1/ECS201C/common-crawl/input.txt` which lists these files.

## Map-reduce framework

You should start by reading up on map reduce.
[The Apache Hadoop tutorial is a good place to start](http://hadoop.apache.org/docs/current/hadoop-mapreduce-client/hadoop-mapreduce-client-core/MapReduceTutorial.html).

You will use the Python package [`mrjob`](https://pythonhosted.org/mrjob/) which implements map reduce and has a nice interface to Amazon's [Elastic Map Reduce (EMR)](https://aws.amazon.com/emr/) service.

To use `mrjob`, you must specify at least one of three functions:
- `mapper`: Takes in a key and a value, outputs any number of key, value pairs
- `combiner`: Takes in a key and an iterator of values and produces one or more key, value pairs
- `reducer`: Takes in a key and an iterator of values

See the [mrjob docs](https://pythonhosted.org/mrjob/job.html#module-mrjob.job) for more information.
You can also specify whether the keys are sorted and a partitioner.
You may want to play around with these options to improve performance.

You can also provide a python list of steps which each has a map-combine-reduce function.
This is useful if you need multiple steps to process your data.

Note: The for first mapper function, by default, the key is `None` and the value is a line of the input file.
It's common to have the first mapper take in a list of files to parse, which you may send parts of to another file.

See the mrjob documentation for a [good example of how to use it](https://pythonhosted.org/mrjob/guides/quickstart.html#writing-your-first-job).

### Working locally

To work locally or on amarillo, first set up your python environment.

```
virtualenv -p python3 venv
source venv/bin/activate
pip install -r requirements.txt
```

Note that after setting up the first time, each time you start a new console you will need to activate the virtual environment (`source venv/bin/activate`).

## Problems

### TLD count

Write a map reduce job to count the number of occurrences of each [top level domain](https://en.wikipedia.org/wiki/Top-level_domain) in the subset of the common crawl downloaded to Amarillo.

**In your report**: Answer the question: What is the top 10 TLDs and how many times to the appear in the dataset?

See `/data1/ECS201C/common-crawl` for the common crawl dataset.

The file `/data1/ECS201C/common-crawl/input.txt` has the list of all of the common crawl files.
Also see `split.py` if you want to see how the larger files were split up.
In HDFS, the files are at `hdfs:///common-crawl/`.
Thus, whether you're using HDFS or native python, you should use different prefixes.

### Average content length per TLD

Extend the above map reduce job (likely with another step) to find the average content length for each TLD.

**In your report**: Answer the question: What is the top 10 TLDs by average content length, and what are these averages?

### Performance comparison

`mrjob` allows you to run your map reduce job in a [variety of ways](https://pythonhosted.org/mrjob/guides/runners.html).

You can use `-r inline` to run a single python process, `-r local` to run multiple python processes (and use `--num-cores` to set the number of cores), ~~and `-r hadoop` to run the local hadoop cluster~~.
Finally, if I can get it set up in time, you can use Amazon's Elastic Map Reduce (EMR) to run on multiple systems with `-r emr`.
I'll post on teams if I can get that working.

**For your report** answer the following
- What is the speedup for 2, 4, 8, 16, 24, 48, 96 threads using just Python
- ~~What is the speedup for 2, 4, 8, 16, 24, 48, 96 threads using hadoop~~

For each graph, explain *why* you are seeing the pattern you're seeing.
