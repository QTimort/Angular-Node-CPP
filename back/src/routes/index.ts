import { Router } from 'express';
import EntryPointRouter from './EntryPoint';

// Init router and path
const router = Router();

// Add sub-routes
router.use('/entryPoint', EntryPointRouter);

// Export the base-router
export default router;
