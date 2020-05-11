window.$docsify = {
  name: 'Sanzo',
  repo: 'https://github.com/Sanzona',
  coverpage: true, // 首页
  loadNavbar: false, // 导航栏
  loadSidebar: true, // 侧边栏
	subMaxLevel: 5, // 目录级别


  alias: { // 嵌套的侧边栏
    './post/_sidebar.md': './_sidebar.md',
    '.*/_navbar.md': './_navbar.md'
  },
}