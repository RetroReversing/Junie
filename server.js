const fs          = require('fs');
const express     = require('express');
const cors        = require('cors');
const compression = require('compression');
const static      = require('serve-static');
const directory   = require('serve-index');

const app = express();

app.use(cors());
app.use(compression({ filter: () => true }));

app.use('/assets', static('./assets'))
app.use('/system', static('./system'))
app.use('/games', static('./games'))

const web_src_path = "./libRetroReversing/websrc/dist/" || "./bin";
const index_html_path = "./libRetroReversing/websrc/dist/index.html" || './bin/index.html';

app.use('/', directory('./games'), (req, res) => {
    const full_path = web_src_path + req.path;
    const file = fs.existsSync(full_path)
        ? full_path
        : index_html_path;

    res.sendFile(file, { root: __dirname });
});

const port = process.env.PORT || 8000;
app.listen(port, () => console.log(`Server running on port ${port}`));
