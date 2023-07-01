package org.fade.algorithm.bloom.filter.redisson;

import org.redisson.Redisson;
import org.redisson.api.RBloomFilter;
import org.redisson.api.RedissonClient;
import org.redisson.config.Config;

/**
 * redisson中布隆过滤器支持
 * @author fade
 */
public class Example {

    public static void main(String[] args) {
        Config config = new Config();
        config.useSingleServer()
                .setAddress("redis://127.0.0.1:6379");
        RedissonClient client = Redisson.create(config);
        RBloomFilter<String> filter = client.getBloomFilter("test");
        filter.tryInit(1000, 0.01);
        filter.add("Hello World!");
        filter.add("Hello Bloom Filter!");
        System.out.println(filter.contains("Hello World!"));
        System.out.println(filter.contains("Hello Bloom Filter!"));
        System.out.println(filter.contains("Hello"));
        client.shutdown();
    }

}
