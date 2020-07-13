function lablegen(hook) {
  hook.doneEach(function() {
    // 每次路由切换时数据全部加载完成后调用，没有参数。
    gitalk = new Gitalk({
      clientID: 'd142f8d9f5e1dd7ff2cc',
      clientSecret: 'f8754fabb05bb9a4464570c5dacd61d474508f30',
      repo: 'Note',
      owner: 'Sanzona',
      admin: ['Sanzona'],
      distractionFreeMode: false,
      id: hex_md5(window.location.pathname + window.location.hash.split('?')[0]),
    });
    // console.log(window.location.href);
    // console.log(window.location.hash.split('?')[0]); // url中的位置标识符
  });
}
$docsify.plugins = [].concat(lablegen, $docsify.plugins);
