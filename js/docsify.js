window.$docsify = {
  name: 'Sanzo',
  repo: 'https://github.com/Sanzona/Note',
  coverpage: true, // 首页
  loadNavbar: true, // 导航栏
  loadSidebar: true, // 侧边栏
  subMaxLevel: 5, // 目录级别
  // themeColor: '#3F51B5',
  // homepage: 'README.md',
  // auto2top: true, //  切换页面自动顶部
  notFoundPage: true,
  // notFoundPage: '404.html',

  // topMargin: 90, // default: 0

  alias: { // 嵌套的侧边栏
    './.*/_sidebar.md': './_sidebar.md',
    // '.*/_navbar.md': './_navbar.md'
  },

  // 完整配置参数
  search: {
    maxAge: 86400000, // 过期时间，单位毫秒，默认一天
    paths: 'auto', // or 'auto'
    placeholder: '搜索',
    noData: '找不到文件',
    // 搜索标题的最大层级, 1 - 6
    depth: 4,
  },

  // 黑夜模式
  darkMode: {
    dark: {
      background: "#1c2022",
      toggleBtnBg: "#34495e",
      textColor: "#b4b4b4"
    },
    light: {
      background: "white",
      toggleBtnBg: "green",
      textColor: "var(--theme-color)"
    },
  },

  // 字数统计
  count:{
    countable: true,
    fontsize: '0.9em',
    color: 'rgb(90,90,90)',
    language: 'chinese',
    // position: "top",
    float: "right",
    isExpected: true, // 时间
},

  // 底部上下篇插件
  pagination: {
    previousText: '上一篇',
    nextText: '下一篇',
    crossChapter: true,
    crossChapterText: true,
},

  // tabs
  tabs: {
    persist: true,
    sync: false,
    theme: 'material',
    tabComments: true,
    tabHeadings: true,
},


// footer: {
//    //copy: '<strong>© 2020 Xhemj</strong>&nbsp;|&nbsp;<a href="/books" target="_blank">官网</a>&nbsp|&nbsp;<a href="https://xhemj.gitee.io/oneQRCodeforPay/" target="_blank">赞助本网站</a>&nbsp|&nbsp;<a href="mailto:xhemj2680@163.com" target="_blank">联系我</a></br><img src="https://xhemj.js.org/logo.png" width="50" height="50">',
//    //auth: '<strong>BY: X H E M J</strong></br><strong>"这只是Xhemj的文档中心而已，也没有什么别的！"</strong><div id="cc-myssl-id"><a href="https://myssl.com/xhemj.js.org?from=mysslid" target="_blank"><img src="https://static.myssl.com/res/images/myssl-id3.png" alt="" style="max-height:50px;display:block;margin:0 auto"></a></br></div>',
//    copy: '<div style="text-align: center;"><iframe src="https://xhemj.js.org/p/badge.html" width="auto" height="auto" frameborder="0" scrolling="no"></iframe></div>',
//    auth: '</br><strong>这只是xhemj的文档中心而已，也没有什么别的。</strong>',
//    pre: '<hr>',
//    style: 'text-align: center;'
// },

};
