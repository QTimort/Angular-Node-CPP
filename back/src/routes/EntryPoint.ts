import StatusCodes from 'http-status-codes';
import { Request, Response, Router } from 'express';
const entryPoint = require('./entry_point.node');

const router = Router();
const { BAD_REQUEST, CREATED, OK } = StatusCodes;


router.get('/screen', async (req: Request, res: Response) => {
    const buffer: ArrayBuffer = entryPoint.entryPoint(0, []);
    const img = Buffer.from(buffer).toString('base64');
    res.set("Content-Type", "image/bmp");
    // todo find a proper way to send an image from a buffer
    return res.status(OK).json({
      Image: img
    });
});


export default router;
