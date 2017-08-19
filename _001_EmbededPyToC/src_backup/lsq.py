import numpy as np
from scipy.optimize import lsq_linear



def least_squares_optimization(H, x, y, R, method=0, lb=[], ub=[]):
    """
    Generic least squares optimization
    """
    num_obs, num_states = np.shape(H)
    x = x[:]
    for k in range(4):
        y_pred = np.zeros((num_obs, 1))
        y_delta = np.zeros((num_obs, 1))
        x_delta = np.zeros((2, 1))
        for i in range(num_obs):
            y_pred[i] = H[i, :].dot(x)
        y_delta = y - y_pred
        W = np.sqrt(np.linalg.inv(R))
        Hw = np.dot(W, H)
        dyw = np.dot(W, y_delta)
        if(method == 0):
            x_delta = np.linalg.lstsq(Hw, dyw)[0]
        elif(method == 1):
            lb = np.arange(2, dtype=float)
            lb[0] = 0
            lb[1] = -80
            ub = np.arange(2, dtype=float)
            ub[0] = 4
            ub[1] = 25
            dyw_trans = []
            dyw_trans[:] = ((dyw.transpose()).tolist())[0]
            res = lsq_linear(Hw, dyw_trans, bounds=(lb, ub),
                             method='trf', lsmr_tol='auto', verbose=0)
            x_delta_list = res['x']
            x_delta[0][0] = x_delta_list[0]
            x_delta[1][0] = x_delta_list[1]
        x = x + x_delta
    return x
