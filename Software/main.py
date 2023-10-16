import psutil

# 获取内存占用率
memory_usage = psutil.virtual_memory()

# 打印内存占用率
print(f"内存占用率: {memory_usage.percent}%")
# 获取CPU使用率
cpu_usage = psutil.cpu_percent(interval=1)  # 可以指定时间间隔
print(f"CPU使用率: {cpu_usage}%")

total_memory_gb = round(memory_usage.total / (2**30), 2)
used_memory_gb = round(memory_usage.used / (2**30), 2)
free_memory_gb = round(memory_usage.free / (2**30), 2)
percent_memory = round(memory_usage.percent, 2)

print(f"GPU总内存: {total_memory_gb} GB")
print(f"GPU已使用: {used_memory_gb} GB")
print(f"GPU可用内存: {free_memory_gb} GB")
print(f"GPU使用率: {percent_memory}%")