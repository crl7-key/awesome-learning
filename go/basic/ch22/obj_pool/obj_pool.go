package obj_pool

import (
	"errors"
	"time"
)

type ReusableObj struct {
}

type ObjPool struct {
	bufChan chan *ReusableObj // 用于欢唱可重用对象
}

// 创建对象池
func NewObjPool(numOfObj int) *ObjPool {
	objPool := ObjPool{}
	objPool.bufChan = make(chan *ReusableObj, numOfObj)

	for i := 0; i < numOfObj; i++ {
		objPool.bufChan <- &ReusableObj{}
	}
	return &objPool
}

func (p *ObjPool) GetObj(timeout time.Duration) (*ReusableObj, error) {
	select {
	case ret := <-p.bufChan:
		return ret, nil
	case <-time.After(timeout): // 超时控制
		return nil, errors.New("time out")
	}
}

// 释放线程对象
func (p *ObjPool) ReleaseObj(obj *ReusableObj) error {
	select {
	case p.bufChan <- obj:
		return nil
	default:
		return errors.New("overflow")
	}
}
