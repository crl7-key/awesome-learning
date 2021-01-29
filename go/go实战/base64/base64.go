package base64

import "encoding/base64"

func Base64Encode(s []byte) []byte {
	buf := make([]byte, base64.StdEncoding.EncodedLen(len(s)))
	base64.StdEncoding.Encode(buf, s)
	return buf
}

func Base64EncodeString(s string) string {
	buf := make([]byte, base64.StdEncoding.EncodedLen(len(s)))
	base64.StdEncoding.Encode(buf, []byte(s))
	return string(buf)
}

func Base64Decode(s []byte) ([]byte, error) {
	buf := make([]byte, base64.StdEncoding.DecodedLen(len(s)))
	n, err := base64.StdEncoding.Decode(buf, s)
	return buf[:n], err
}

func Base64DecodeString(s string) (string, error) {
	buf := make([]byte, base64.StdEncoding.DecodedLen(len(s)))
	n, err := base64.StdEncoding.Decode(buf, []byte(s))
	return string(buf[:n]), err
}
