from mrjob.job import MRJob

import boto3
import botocore
from gzipstream import GzipStreamFile
from tempfile import TemporaryFile

def getCCFile(name):
    boto_config = botocore.client.Config(
            signature_version=botocore.UNSIGNED,
            read_timeout=180,
            retries={'max_attempts' : 20})
    s3client = boto3.client('s3', config=boto_config)
    try:
        s3client.head_bucket(Bucket='commoncrawl')
    except botocore.exceptions.ClientError as exception:
        return
    try:
        s3client.head_object(Bucket='commoncrawl',
                Key=name)
    except botocore.client.ClientError as exception:
        return
    try:
        temp = TemporaryFile(mode='w+b',
                dir='/tmp/')
        s3client.download_fileobj('commoncrawl', name, temp)
    except botocore.client.ClientError as exception:
        return
    temp.seek(0)
    return GzipStreamFile(temp)

class Counter(MRJob):

    def mapper(self, key, value):
        for i in value.split(' '):
            if all([ord(j) < 128 for j in i]):
                yield i, 1

    def combiner(self, key, values):
        yield key, sum(values)

    def reducer(self, key, values):
        yield key, sum(values)

class Grep(MRJob):

    def mapper(self, key, value):
        for i in value.split(' '):
            if i.lower() == "goodbye":
                yield "goodbye", 1

    def reducer(self, key, values):
        yield key, sum(values)

class CountTLDs(MRJob):

    def mapper(self, key, value):
        for line in getCCFile(value):
            if line.startswith('WARC-Target-URI'):
                url = line.split(' ')[1].split('/')
                tld = url[2].split('.')[-1].split(":")[0]
                yield tld, 1

    def reducer(self, key, values):
        yield key, sum(values)

if __name__=='__main__':
    CountTLDs.run()
