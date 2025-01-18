from pyspark.sql import SparkSession
from pyspark.sql.functions import col, expr


def process_large_dataset(input_path, output_path):
    spark = SparkSession.builder \
        .appName("LargeScaleIDProcessing") \
        .getOrCreate()

    spark.conf.set("spark.sql.shuffle.partitions", "200")

    df = spark.read.text(input_path).withColumnRenamed("value", "id_str")
    df = df.withColumn("id", col("id_str").cast("int")).drop("id_str")

    freq_df = df.groupBy("id").count().withColumnRenamed("count", "freq")
    result_df = freq_df.alias("t1").join(
        freq_df.alias("t2"),
        expr("t2.id = t1.id + 10")
    ).select(
        col("t1.id").alias("id1"),
        col("t2.id").alias("id2"),
        (col("t1.freq") * col("t2.freq")).alias("pair_count")
    ).orderBy(col("pair_count").desc())

    result_df.coalesce(1).write.mode("overwrite").csv(output_path)
    spark.stop()


if __name__ == "__main__":
    process_large_dataset("data/input.txt", "data/output_pairs.csv")
