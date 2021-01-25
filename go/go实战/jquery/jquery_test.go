package jquery_test

import (
	"fmt"
	"log"
	"os"
	"strings"
	"testing"
	"text/template"

	"github.com/PuerkitoBio/goquery"
)

func ExampleScrape() {
	doc, err := goquery.NewDocument("http://www.bilibili.com")
	if err != nil {
		log.Fatal(err)
	}

	// Find the review items
	doc.Find(".sidebar-reviews article .content-block").Each(func(i int, s *goquery.Selection) {
		// For each item found, get the band and title
		band := s.Find("a").Text()
		title := s.Find("i").Text()
		fmt.Printf("Review %d: %s - %s\n", i, band, title)
	})
}
func TestExample(t *testing.T) {
	ExampleScrape()
}

func getlinkScrape() {
	doc, err := goquery.NewDocument("http://jonathanmh.com")
	if err != nil {
		log.Fatal(err)
	}

	doc.Find("body a").Each(func(index int, item *goquery.Selection) {
		linkTag := item
		link, _ := linkTag.Attr("href")
		linkText := linkTag.Text()
		fmt.Printf("Link #%d: '%s' - '%s'\n", index, linkText, link)
	})
}

func TestGetLink(t *testing.T) {
	getlinkScrape()
}

const rstLink = "`{{.Text}} <{{.Href}}>`_\n"

type htmlLink struct {
	Text string
	Href string
}

func TestHtmlToreStructuredText(t *testing.T) {
	url := "https://www.bilibili.com"

	doc, err := goquery.NewDocument(url)
	if err != nil {
		panic(err)
	}

	tmpl := template.Must(template.New("test").Parse(rstLink))
	doc.Find("a").Each(func(_ int, link *goquery.Selection) {
		text := strings.TrimSpace(link.Text())
		href, ok := link.Attr("href")
		if ok {
			tmpl.Execute(os.Stdout, &htmlLink{text, href})
		}
	})
}
