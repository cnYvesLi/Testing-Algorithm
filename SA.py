import random
import matplotlib.pyplot as plt
import math


def func(x, y):
    return 4 * x ** 2 - 2.1 * x ** 4 + x ** 6 / 3 + x * y - 4 * y ** 2 + 4 * y ** 4


class SA:
    def __init__(self, function, iteration=100, T0=100, Tf=0.01, alpha=0.99, data_range=None, show=False):
        if data_range is None:
            data_range = [-5, 5]
        self.data_range = data_range
        self.func = function
        self.iter = iteration
        self.T0 = T0
        self.T = T0
        self.Tf = Tf
        self.alpha = alpha
        self.x = [random.uniform(data_range[0], data_range[1]) for _ in range(iteration)]
        self.y = [random.uniform(data_range[0], data_range[1]) for _ in range(iteration)]
        self.best_val = [float('inf')] * iteration
        self.history = {'t': [], 'v': []}
        self.show = show

    def Metrospolis(self, f, f_new):
        if f_new <= f:
            return True
        else:
            p = math.exp((f - f_new) / self.T)
            if random.random() < p:
                return True
            else:
                return False

    def new_data(self):
        for i in range(self.iter):
            f = self.func(self.x[i], self.y[i])
            while True:
                x_new = self.x[i] + self.T * random.uniform(-1, 1)
                y_new = self.y[i] + self.T * random.uniform(-1, 1)
                if (self.data_range[0] < x_new < self.data_range[1]) and (self.data_range[0] < y_new < self.data_range[1]):
                    break
            # print(self.x[i], x_new, self.y[i], y_new)
            f_new = self.func(x_new, y_new)
            if self.Metrospolis(f, f_new):
                self.x[i] = x_new
                self.y[i] = y_new

    def best(self):
        val = float("inf")
        idx = 0
        for i in range(self.iter):
            new_val = self.func(self.x[i], self.y[i])
            if new_val < val:
                val = new_val
                idx = i
        self.history['t'].append(self.T)
        self.history['v'].append(val)
        return idx

    def data_show(self, epoch, idx):
        if self.show is True:
            print(f"T:{self.history['t'][epoch]}, V:{self.history['v'][epoch]}, Pos:{self.x[idx], self.y[idx]}")

    def run(self):
        epoch = 0
        idx = 0
        while self.T > self.Tf:
            epoch += 1
            self.new_data()
            idx = self.best()
            self.data_show(epoch - 1, idx)
            self.T = self.T * self.alpha
        print(f"Pos:{self.x[idx], self.y[idx]}, Val:{self.history['v'][epoch - 1]}")


random.seed(42)
sa = SA(func)
sa.run()
plt.plot(sa.history['t'], sa.history['v'])
plt.title("SA")
plt.xlabel("T")
plt.ylabel("Val")
plt.gca().invert_xaxis()
plt.show()
