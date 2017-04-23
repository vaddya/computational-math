# coding=utf-8

import math
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
from mpl_toolkits.mplot3d import Axes3D
from scipy import integrate, interpolate, optimize
from matplotlib import rc
from matplotlib.ticker import FormatStrFormatter
font = {'family': 'Arial', 'weight': 'normal'}
rc('font', **font)

# Нахождение длины балки
def fun(x: float):
    def inner(z: float):
        return math.exp(-0.9 * z)/(z + x)
    return integrate.quad(inner, 0, 20)[0] - 0.1957981 * x;

x_star, = optimize.fsolve(fun, (4 - 1) / 2)
print('x* = {x}'.format(x=x_star))

l = 50 * x_star
print('Длина балки l = {l}'.format(l=l))

# Начальные условия
def get_y0(p: int):
    y0_1 = 0
    y0_2 = 0
    y0_3 = p * l / 75 * 10 ** (-7)
    y0_4 = p * 3.8 / 75 * 10 ** (-7)
    return np.array([y0_1, y0_2, y0_3, y0_4])

# Значения нагрузки на балку
def get_p():
    return np.arange(500, 1000 + 1, 100)
p0 = 750

# Вычисление значения в точке t
def evaluate(y: np.array, t: float, a: float, b: float):
    i = a * (1 + 4 * math.exp(-b * t/l))
    di1 = 4 * a * (-b) * math.exp(-b * t/l) / l
    di2 = 4 * a * (-b) * (-b) * math.exp(-b * t/l) / l
    y41 = -1 * di2 / i
    y42 = -2 * di1 / i
    y4 = y41 * y[2] + y42 * y[3]
    return np.array([y[1], y[2], y[3], float(y4)])

# Решение дифференциального уравнения
# Пределы поиска значений y(t)
t0 = l - 5
tn = l + 5
th = 0.01
t = np.arange(t0, tn, th)

# Итерация по всем значениям P
values = []
for p in get_p():
    y0 = get_y0(p)
    res, info = integrate.odeint(evaluate, y0, t, args=(5,6), atol=1e-8, full_output=True)
    y = np.transpose(res)[0]
    values.append(y)

# График y(t)
axes = plt.figure(figsize=(10,7)).gca()
for i in range(len(get_p())):
    axes.plot(t, values[i], linewidth=1.5, label='$P = {p}$'.format(p=get_p()[i]))
axes.plot([l, l], [0, 0.008], color='0.7', linewidth=1.5, linestyle='--', label='$t = l \simeq {l}$'.format(l=math.ceil(l)))
axes.legend(loc='upper left', fontsize=15)
axes.set_xlabel('$t$', fontsize=20, labelpad=20)
axes.set_ylabel('$y(t)$', fontsize=20, labelpad=20)
axes.tick_params(labelsize=15, pad=10)
axes.set_xlim([l-5, l+5])
plt.tight_layout()
plt.savefig('./pics/p.png')
plt.show()

# Зависимость значения y(l) от P
p_interps = np.array([])
l_values = []
for i in range(len(values)):
    p_interp = interpolate.interp1d(t, values[i])
    p_interps = np.append(p_interps, p_interp)
    l_value = p_interp(l)
    l_values.append(l_value)
    print('P = {p}, f(l) = {value}'.format(p=get_p()[i], value=l_value))

# График S(P)
axes = plt.figure(figsize=(10,7)).gca()
axes.plot(get_p(), l_values, linewidth=1.5, marker='s', label='$f(l) = f(P)$')
axes.plot([p0, p0], [0.0008, 0.0018], linewidth=1.5, color='0.7', linestyle='--', label='$P = P_0 = {p0}$'.format(p0=p0))
axes.legend(loc='upper left', fontsize=20)
axes.set_xlabel('$P$', fontsize=20, labelpad=20)
axes.set_ylabel('$f(l)$', fontsize=20, labelpad=20)
axes.tick_params(labelsize=15, pad=10)
axes.set_xlim([450,1050])
plt.tight_layout()
plt.savefig('./pics/l.png')
plt.show()

# Поиск значения S(P0) = S(750)
l_interp = interpolate.interp1d(get_p(), l_values, kind='cubic')
l_p0 = l_interp(p0)
print('P = {p}, S(P) = {value}'.format(p=p0, value=l_p0))

# Анализ влияния погрешности начальных условий на решение
# Пределы варьирования коээфициентов
a0 = 5
b0 = 6
h = 0.01
a = np.arange(0.9 * a0, 1.1 * a0 + h, h)
b = np.arange(0.9 * b0, 1.1 * b0 + h, h)
g = np.meshgrid(a, b, indexing='ij')

# Итерация по всем значения alpha и beta
values = []
for alpha in a:
    tmp = []
    for beta in b:
        y0 = get_y0(p0)
        res = integrate.odeint(evaluate, y0, t, args=(alpha,beta), atol=1e-8)
        y = np.transpose(res)[0]
        p_interp = interpolate.interp1d(t, y)
        l_value = p_interp(l)
        tmp.append(np.abs((l_value - l_p0)))
    values.append(tmp)
values = np.array(tmp)        

# График epsilon(alpha, beta)
axes = plt.figure(figsize=(12,8)).gca(projection='3d')
axes.plot_surface(g[0], g[1], values, alpha=0.4, cmap=cm.coolwarm)
axes.view_init(elev=30., azim=12)
axes.zaxis.set_major_formatter(FormatStrFormatter('%.0e', ))
axes.set_xlabel(r'$\alpha$', fontsize=25, labelpad=20)
axes.set_ylabel(r'$\beta$', fontsize=25, labelpad=25)
axes.set_zlabel(r'$\varepsilon(\alpha, \beta)$', fontsize=25, labelpad=35)
axes.set_xlim(min(a), max(a))
axes.set_ylim(min(b), max(b))
axes.tick_params(labelsize=15, pad=10)
axes.tick_params('z', labelsize=15, pad=15)
plt.tight_layout()
plt.savefig('./pics/ab.png')
plt.show()