package code

type Data struct {
	Id         int    `json:"id" form:"id"`
	Name       string `json:"name" form:"name"`
	Ip         string `json:"ip" form:"ip"`
	Port       int    `json:"port" form:"port"`
	EnableLogs bool   `json:"enableLogs" form:"enableLogs"`
}
